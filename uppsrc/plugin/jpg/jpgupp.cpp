#include <Draw/Draw.h>
// #include <setjmp.h>
#include "jpg.h"
#define HAVE_BOOLEAN
#define boolean int
#undef FAR
extern "C" {
#include "lib/jinclude.h"
#include "lib/jpeglib.h"
#include "lib/jerror.h"
}
#undef XINT32


NAMESPACE_UPP

#define LLOG(x)  // LOG(x)

static void NoOutput(j_common_ptr cinfo)
{
}

enum
{
	STREAM_BUF_SIZE = 16384,
	ROW_BUF_SIZE    = 16384,
};

struct jpg_stream_destination_mgr
{
	jpeg_destination_mgr  pub;
	Stream               *stream;
	JOCTET               *buffer;
};

typedef jpg_stream_destination_mgr *stream_dest_ptr;

static void init_destination(j_compress_ptr cinfo)
{
	stream_dest_ptr dest = (stream_dest_ptr)cinfo->dest;
	dest->buffer = (JOCTET *)
		(*cinfo->mem->alloc_small)((j_common_ptr)cinfo, JPOOL_IMAGE,
			STREAM_BUF_SIZE * sizeof(JOCTET));
	dest->pub.next_output_byte = dest->buffer;
	dest->pub.free_in_buffer = STREAM_BUF_SIZE;
}

static boolean empty_output_buffer(j_compress_ptr cinfo)
{
	stream_dest_ptr dest = (stream_dest_ptr)cinfo->dest;
	dest->stream->Put(dest->buffer, STREAM_BUF_SIZE * sizeof(JOCTET));
	dest->pub.next_output_byte = dest->buffer;
	dest->pub.free_in_buffer = STREAM_BUF_SIZE;
	return true;
}

static void term_destination(j_compress_ptr cinfo)
{
	stream_dest_ptr dest = (stream_dest_ptr)cinfo->dest;
	size_t done = STREAM_BUF_SIZE - dest->pub.free_in_buffer;
	if(done > 0)
		dest->stream->Put(dest->buffer, done * sizeof(JOCTET));
}

static void jpeg_stream_dest(j_compress_ptr cinfo, Stream& stream)
{
	if(cinfo->dest == NULL)
		cinfo->dest = (jpeg_destination_mgr *)
			(*cinfo->mem->alloc_small)((j_common_ptr)cinfo, JPOOL_PERMANENT,
				sizeof(jpg_stream_destination_mgr));

	stream_dest_ptr dest = (stream_dest_ptr)cinfo->dest;
	dest->pub.init_destination    = init_destination;
	dest->pub.empty_output_buffer = empty_output_buffer;
	dest->pub.term_destination    = term_destination;
	dest->pub.next_output_byte    = NULL;
	dest->pub.free_in_buffer      = 0;
	dest->stream                  = &stream;
	dest->buffer                  = NULL;
}

struct jpg_stream_source_mgr
{
	jpeg_source_mgr pub;
	Stream         *stream;
	JOCTET         *buffer;
	bool            start_of_file;
};

typedef jpg_stream_source_mgr *stream_src_ptr;

static void init_source(j_decompress_ptr cinfo)
{
	stream_src_ptr src = (stream_src_ptr)cinfo->src;
	src->start_of_file = true;
}

static boolean fill_input_buffer(j_decompress_ptr cinfo)
{
	stream_src_ptr src = (stream_src_ptr)cinfo->src;
	size_t nbytes = src->stream->Get(src->buffer, STREAM_BUF_SIZE * sizeof(JOCTET));
	if(nbytes == 0)
	{
		if(src->start_of_file)
			ERREXIT(cinfo, JERR_INPUT_EMPTY);
		WARNMS(cinfo, JWRN_JPEG_EOF);
		/* Insert a fake EOI marker */
		src->buffer[0] = (JOCTET) 0xFF;
		src->buffer[1] = (JOCTET) JPEG_EOI;
		nbytes = 2;
	}

	src->pub.next_input_byte = src->buffer;
	src->pub.bytes_in_buffer = nbytes;
	src->start_of_file       = false;

	return true;
}

static void skip_input_data(j_decompress_ptr cinfo, long num_bytes)
{
	stream_src_ptr src = (stream_src_ptr)cinfo->src;
	int above = num_bytes - src->pub.bytes_in_buffer;
	if(above < 0)
	{ // we're still within the input buffer
		src->pub.next_input_byte += num_bytes;
		src->pub.bytes_in_buffer = -above;
	}
	else
	{
		src->stream->Seek(src->stream->GetPos() + above);
		src->start_of_file = false;
		src->pub.next_input_byte = NULL;
		src->pub.bytes_in_buffer = 0;
	}
}

static void term_source(j_decompress_ptr cinfo)
{
	stream_src_ptr src = (stream_src_ptr)cinfo->src;
	src->pub.next_input_byte = NULL;
	src->pub.bytes_in_buffer = 0;
}

static void jpeg_stream_src(j_decompress_ptr cinfo, Stream& stream)
{
	stream_src_ptr src = (stream_src_ptr)cinfo->src;
	if(src == NULL)
	{
		cinfo->src = (jpeg_source_mgr *)
			(*cinfo->mem->alloc_small)((j_common_ptr)cinfo, JPOOL_PERMANENT,
				sizeof(jpg_stream_source_mgr));
		src = (stream_src_ptr)cinfo->src;
		src->buffer = (JOCTET *)(*cinfo->mem->alloc_small)((j_common_ptr)cinfo,
			JPOOL_PERMANENT, STREAM_BUF_SIZE * sizeof(JOCTET));
	}

	src->pub.init_source       = init_source;
	src->pub.fill_input_buffer = fill_input_buffer;
	src->pub.skip_input_data   = skip_input_data;
	src->pub.resync_to_restart = jpeg_resync_to_restart;
	src->pub.term_source       = term_source;
	src->pub.bytes_in_buffer   = 0;
	src->pub.next_input_byte   = NULL;
	src->stream                = &stream;
}


struct jpeg_longjmp_error_mgr : public jpeg_error_mgr {
//	jmp_buf jmpbuf;
};

struct JpegErrorException {};

static void error_exit(j_common_ptr cinfo)
{
	(*cinfo->err->output_message)(cinfo);
	jpeg_longjmp_error_mgr *jlem = (jpeg_longjmp_error_mgr *)cinfo->err;
	throw JpegErrorException();
//	longjmp(jlem->jmpbuf, 1);
}

class JPGRaster::Data {
	friend class JPGRaster;

public:
	Data(JPGRaster& owner);
	~Data();

	bool Create(Stream& stream);
	void Construct();
	void Free();
	Raster::Info GetInfo();
	Raster::Line GetLine(int line);
	void ScanMetaData();
	void ScanExifData(const char *begin);
	Value GetMetaData(String id);
	void EnumMetaData(Vector<String>& id_list);
	String GetThumbnail();

private:
	bool Init();

	int     Exif16(const char *s) { return exif_big_endian ? Peek16be(s) : Peek16le(s); }
	int     Exif32(const char *s) { return exif_big_endian ? Peek32be(s) : Peek32le(s); }
	double  ExifF5(const char *s);

	enum IFD_TYPE { BASE_IFD, GPS_IFD };
	int  ExifDir(const char *begin, int offset, IFD_TYPE type);

private:
	JPGRaster& owner;
	Stream *stream;
	int64 stream_fpos;

	RasterFormat format;
	RGBA palette[256];

	VectorMap<String, Value> metadata;
	int                      thumboffset, thumblen;

	struct jpeg_decompress_struct cinfo;
	struct jpeg_longjmp_error_mgr jerr;

	Size size;
	Size dot_size;
	int row_bytes;
	int row_bytes_4;
	bool finish;
	bool exif_big_endian;

	int next_line;
};

void JPGRaster::Data::Construct()
{
	stream = NULL;
	size = dot_size = Null;
	next_line = 0;
	finish = false;

	try {
		jpeg_create_decompress(&cinfo);
	}
	catch(JpegErrorException) {}
}

JPGRaster::Data::Data(JPGRaster& owner_)
: owner(owner_)
{
	Construct();
}

void JPGRaster::Data::Free()
{
//	if(setjmp(jerr.jmpbuf))
//		return;
	try {
		if(finish)
			jpeg_abort_decompress(&cinfo);
		jpeg_destroy_decompress(&cinfo);
	}
	catch(JpegErrorException) {}
}

JPGRaster::Data::~Data()
{
	Free();
}

bool JPGRaster::Data::Create(Stream& stream_)
{
	stream = &stream_;
	stream_fpos = stream->GetPos();
	cinfo.err = jpeg_std_error(&jerr);
	cinfo.err->output_message = &NoOutput;
	cinfo.dct_method = JDCT_IFAST;
	jerr.error_exit = error_exit;
	return Init();
}

void JPGRaster::Data::ScanMetaData()
{
	if(!metadata.IsEmpty())
		return;
	for(jpeg_saved_marker_ptr p = cinfo.marker_list; p; p = p->next) {
		String data(p->data, p->data_length);
		String key;
		if(p->marker == JPEG_COM)
			key = "COM";
		else if(p->marker >= JPEG_APP0 && p->marker <= JPEG_APP0 + 15) {
			key = NFormat("APP%d", p->marker - JPEG_APP0);
			if(p->marker == JPEG_APP0 + 1 && !memcmp(data, "Exif\0\0", 6))
				ScanExifData(data.GetIter(6));
		}
		if(metadata.Find(key) >= 0) {
			for(int i = 1;; i++) {
				String suffix;
				suffix << key << '$' << i;
				if(metadata.Find(suffix) < 0) {
					key = suffix;
					break;
				}
			}
		}
		metadata.Add(key, data);
	}
}

double JPGRaster::Data::ExifF5(const char *s)
{
	unsigned num = Exif32(s + 0);
	unsigned den = Exif32(s + 4);
	return num / (double)(den ? den : 1);
}

int JPGRaster::Data::ExifDir(const char *begin, int offset, IFD_TYPE type)
{
	const char *e = begin + offset;
	int nitems = Exif16(e);
//	puts(NFormat("directory %08x: %d items", dir, nitems));
	e += 2;
	for(int i = 0; i < nitems; i++, e += 12) {
		int tag = Exif16(e);
		int fmt = Exif16(e + 2);
		int count = Exif32(e + 4);
		static const int fmtlen[] = {
			1, 1, 2, 4, 8, 1, 1, 2, 4, 8, 4, 8
		};
		int len = 0;
		if(fmt > 0 && fmt <= __countof(fmtlen))
			len = fmtlen[fmt - 1] * count;
		const char *data = e + 8;
		if(len > 4)
			data = begin + Exif32(data);
//		puts(NFormat("[%d]: tag %04x fmt %d, count %d, data %s",
//			i, tag, fmt, count, BinHexEncode(data, data + len)));
		if(type == BASE_IFD) {
			if(tag == 0x8825) {
				int offset = Exif32(data);
	//			puts(NFormat("GPS IFD at %08x", offset));
				ExifDir(begin, offset, GPS_IFD);
			}
		}
		else if(type == GPS_IFD) {
			if((tag == 2 || tag == 4) && fmt == 5 && count == 3) {
				metadata.Add(tag == 2 ? "GPSLatitude" : "GPSLongitude",
					ExifF5(data + 0) + ExifF5(data + 8) / 60 + ExifF5(data + 16) / 3600);
//				puts(NFormat("GPSLatitude: %n %n %n", n1, n2, n3));
			}
			else if(tag == 6 && fmt == 5 && count == 1)
				metadata.Add("GPSAltitude", ExifF5(data));
		}
	}
	int nextoff = Exif32(e);
//	puts(NFormat("next offset = %08x", nextoff));
	return nextoff;
}

void JPGRaster::Data::ScanExifData(const char *begin)
{
	const char *p = begin;
	if(p[0] == 'I' && p[1] == 'I')
		exif_big_endian = false;
	else if(p[0] == 'M' && p[1] == 'M')
		exif_big_endian = true;
	else
		return;
	for(int diroff = Exif32(p + 4); diroff; diroff = ExifDir(begin, diroff, BASE_IFD))
		;
}

Value JPGRaster::Data::GetMetaData(String id)
{
	ScanMetaData();
	return metadata.Get(id, Value());
}

void JPGRaster::Data::EnumMetaData(Vector<String>& id_list)
{
	ScanMetaData();
	id_list <<= metadata.GetKeys();
}

String JPGRaster::Data::GetThumbnail()
{
	ScanMetaData();
	String app1 = GetMetaData("APP1");
	if(!app1.GetCount())
		return Null;
	const char *begin = ~app1 + 6;
	const char *end = app1.End();
	const char *p = begin + Exif32(begin + 4);
	if(p + 2 >= end) return Null;
	p += Exif16(p) * 12 + 2;
	if(p + 4 >= end) return Null;
	p = begin + Exif32(p);
	if(p <= begin || p + 2 >= end) return Null;
	word count = Exif16(p);
	p += 2;
	dword offset = 0;
	dword len = 0;
	for(int n = 0; n < count; n++) {
		if(p + 12 >= end) Null;
		if(Exif32(p + 4) == 1) {
			dword val = 0;
			switch(Exif16(p + 2)) {
			case 4:
			case 9:
				val = Exif32(p + 8);
				break;
			case 3:
			case 8:
				val = Exif16(p + 8);
				break;
			}
			if(val)
				switch(Exif16(p)) {
				case 0x201:
					offset = val;
					break;
				case 0x202:
					len = val;
					break;
				}
		}
		p += 12;
	}
	return offset && len && begin + offset + len < end ? String(begin + offset, len) : String();
}

bool JPGRaster::Data::Init()
{
//	if(setjmp(jerr.jmpbuf))
//		return false;

	try {
		jpeg_stream_src(&cinfo, *stream);
		jpeg_save_markers(&cinfo, JPEG_COM, 0xFFFF);
		for(int i = 0; i <= 15; i++)
			jpeg_save_markers(&cinfo, JPEG_APP0 + i, 0xFFFF);
		jpeg_read_header(&cinfo, TRUE);
		jpeg_start_decompress(&cinfo);
	
		switch(cinfo.output_components) {
			case 1: {
				format.Set8();
				for(int i = 0; i < 256; i++) {
					RGBA rgba;
					rgba.r = rgba.g = rgba.b = i;
					rgba.a = 255;
					palette[i] = rgba;
				}
				break;
			}
			case 3: {
				format.Set24le(0xFF, 0xFF00, 0xFF0000);
				break;
			}
			default: {
				LLOG("JPGRaster: invalid number of components: " << (int)cinfo.output_components);
				return false;
			}
		}
	
		size.cx = cinfo.output_width;
		size.cy = cinfo.output_height;
	
		row_bytes = cinfo.output_components * size.cx;
		row_bytes_4 = (row_bytes + 3) & -4;
	
		double dot_scaling = (cinfo.density_unit == 1 ? 600 : cinfo.density_unit == 2 ? 600.0 / 2.54 : 0);
		if(dot_scaling && cinfo.X_density > 0) {
			dot_size.cx = fround(cinfo.image_width  * dot_scaling / cinfo.X_density);
			dot_size.cy = fround(cinfo.image_height * dot_scaling / cinfo.Y_density);
		}
	
		finish = true;
		return true;
	}
	catch(JpegErrorException) {
		return false;
	}
}

Raster::Info JPGRaster::Data::GetInfo()
{
	Raster::Info info;
	try {
		info.bpp = 24;
		info.colors = 0;
		info.dots = dot_size;
		info.hotspot = Null;
		info.kind = IMAGE_OPAQUE;
	}
	catch(Exc e) {
		LLOG(e);
	}
	return info;
}

Raster::Line JPGRaster::Data::GetLine(int line)
{
	byte *rowbuf = new byte[row_bytes_4];

//	if(setjmp(jerr.jmpbuf))
//		return Raster::Line(rowbuf, &owner, true);

	try {
		ASSERT(line >= 0 && line < size.cy);
		if(line < next_line) {
			stream->Seek(stream_fpos);
			Stream *s = stream;
			Free();
			Construct();
			Create(*s);
			next_line = 0;
			LOG("Seek back");
		}
		JSAMPROW rowptr[] = { (JSAMPROW)rowbuf };
		while(next_line++ < line)
			jpeg_read_scanlines(&cinfo, rowptr, 1);
		jpeg_read_scanlines(&cinfo, rowptr, 1);
		return Raster::Line(rowbuf, &owner, true);
	}
	catch(JpegErrorException) {
		return Raster::Line(rowbuf, &owner, true);
	}
}

JPGRaster::JPGRaster()
{
}

JPGRaster::~JPGRaster()
{
}

bool JPGRaster::Create()
{
	ASSERT(sizeof(JSAMPLE) == sizeof(byte));
	data = new Data(*this);
	return data->Create(GetStream());
}

Size JPGRaster::GetSize()
{
	return data->size;
}

Raster::Info JPGRaster::GetInfo()
{
	ASSERT(data);
	Raster::Info info;
	info.kind = IMAGE_OPAQUE;
	if(data->cinfo.output_components == 1) {
		info.bpp = 8;
		info.colors = 256;
	}
	else {
		info.bpp = 24;
		info.colors = 0;
	}
	info.dots = data->dot_size;
	info.hotspot = Null;
	return info;
}

Value JPGRaster::GetMetaData(String id)
{
	ASSERT(data);
	return data->GetMetaData(id);
}

void JPGRaster::EnumMetaData(Vector<String>& id_list)
{
	ASSERT(data);
	data->EnumMetaData(id_list);
}

Raster::Line JPGRaster::GetLine(int line)
{
	ASSERT(data);
	return data->GetLine(line);
}

const RGBA *JPGRaster::GetPalette()
{
	ASSERT(data);
	return data->palette;
}

const RasterFormat *JPGRaster::GetFormat()
{
	ASSERT(data);
	return &data->format;
}

class JPGEncoder::Data {
public:
	Data();
	~Data();

	void Start(Stream& stream, Size size, int quality);
	void WriteLineRaw(const byte *rgba);

private:
	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;
	Size size;
	int line;
};

JPGEncoder::Data::Data()
{
	cinfo.err = jpeg_std_error(&jerr);
	cinfo.err->output_message = &NoOutput;
	jpeg_create_compress(&cinfo);
	cinfo.dct_method = JDCT_IFAST;
}

JPGEncoder::Data::~Data()
{
	try {
		jpeg_destroy_compress(&cinfo);
	}
	catch(JpegErrorException) {}
}

void JPGEncoder::Data::Start(Stream& stream, Size size_, int quality)
{
	try {
		size = size_;
	
		jpeg_stream_dest(&cinfo, stream);
	
		cinfo.image_width = size.cx;
		cinfo.image_height = size.cy;
		cinfo.input_components = 3; // # of color components per pixel
		cinfo.in_color_space = JCS_RGB; // colorspace of input image
	
		jpeg_set_defaults(&cinfo);
	
	/*
		if(dot_size.cx || dot_size.cy)
		{ // set up image density
			cinfo.density_unit = 1; // dots per inch
			cinfo.X_density = dot_size.cx ? fround(size.cx * 600.0 / dot_size.cx) : 0;
			cinfo.Y_density = dot_size.cy ? fround(size.cy * 600.0 / dot_size.cy) : 0;
		}
	*/
	
		jpeg_set_quality(&cinfo, quality, true); // limit to baseline-JPEG values
		jpeg_start_compress(&cinfo, true);
	
		line = 0;
	
		ASSERT(sizeof(JSAMPLE) == sizeof(byte));
	}
	catch(JpegErrorException) {}
}

void JPGEncoder::Data::WriteLineRaw(const byte *s)
{
	try {
		JSAMPROW rowptr[] = { (byte *)s };
		jpeg_write_scanlines(&cinfo, rowptr, 1);
		if(++line >= size.cy)
			jpeg_finish_compress(&cinfo);
	}
	catch(JpegErrorException) {}
}

JPGEncoder::JPGEncoder(int quality_)
: quality(quality_)
{
	format.Set24le(0xff, 0xff00, 0xff0000);
}

JPGEncoder::~JPGEncoder()
{
}

int JPGEncoder::GetPaletteCount()
{
	return 0;
}

void JPGEncoder::Start(Size sz)
{
	data = new Data;
	data->Start(GetStream(), sz, quality);
}

void JPGEncoder::WriteLineRaw(const byte *s)
{
	data->WriteLineRaw(s);
}

Image JPGRaster::GetExifThumbnail()
{
	ASSERT(data);
	StringStream ss(data->GetThumbnail());
	return StreamRaster::LoadStringAny(ss);
}

END_UPP_NAMESPACE
