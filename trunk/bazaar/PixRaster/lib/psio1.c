/*====================================================================*
 -  Copyright (C) 2001 Leptonica.  All rights reserved.
 -  This software is distributed in the hope that it will be
 -  useful, but with NO WARRANTY OF ANY KIND.
 -  No author or distributor accepts responsibility to anyone for the
 -  consequences of using this software, or for whether it serves any
 -  particular purpose or works at all, unless he or she says so in
 -  writing.  Everyone is granted permission to copy, modify and
 -  redistribute this source code, for commercial or non-commercial
 -  purposes, with the following restrictions: (1) the origin of this
 -  source code must not be misrepresented; (2) modified versions must
 -  be plainly marked as such; and (3) this notice may not be removed
 -  or altered from any source or modified source distribution.
 *====================================================================*/

/*
 *  psio1.c
 *
 *    |=============================================================|
 *    |                         Important note                      |
 *    |=============================================================|
 *    |Some of these functions require libtiff and libjpeg.         |
 *    |If you do not have both of these libraries, you must set     |
 *    |     #define  USE_PSIO     0                                 |
 *    |in environ.h.  This will link psio1stub.c                    |
 *    |=============================================================|
 *
 *     This is a PostScript "device driver" for wrapping images
 *     in PostScript.  The images can be rendered by a PostScript
 *     interpreter for viewing, using evince or gv.  They can also be
 *     rasterized for printing, using gs or an embedded interpreter
 *     in a PostScript printer.  And they can be converted to a pdf
 *     using gs (ps2pdf).
 *
 *     Convert specified files to PS
 *          l_int32          convertFilesToPS()
 *          l_int32          sarrayConvertFilesToPS()
 *          l_int32          convertFilesFittedToPS()
 *          l_int32          sarrayConvertFilesFittedToPS()
 *          l_int32          writeImageCompressedToPSFile()
 *
 *     Convert mixed text/image files to PS
 *          l_int32          convertSegmentedPagesToPS()
 *          l_int32          pixWriteSegmentedPageToPS()
 *          l_int32          pixWriteMixedToPS()
 *
 *     Convert any image file to PS for embedding
 *          l_int32          convertToPSEmbed()
 *
 *  These PostScript converters are used in three different ways.
 *  All images are output with bounding box hints and page numbers.
 *
 *  (1) For embedding a PS file in a program like TeX.
 *      convertToPSEmbed() handles this for levels 1, 2 and 3 output,
 *      and prog/converttops wraps this in an executable.
 *      converttops is a generalization of Thomas Merz's jpeg2ps wrapper,
 *      in that it works for all types (formats, depth, colormap)
 *      of input images and gives PS output in one of these formats
 *        * level 1 (uncompressed)
 *        * level 2 (compressed ccittg4 or dct)
 *        * level 3 (compressed flate)
 *
 *  (2) For composing a set of pages with any number of images
 *      painted on them, in either level 2 or level 3 formats.
 *
 *  (3) For printing a page image or a set of page images, at a
 *      resolution that optimally fills the page, using
 *      convertFilesFittedToPS().
 *
 *  The top-level calls of utilities in category 2, which can compose
 *  multiple images on a page, and which generate a PostScript file for
 *  printing or display (e.g., conversion to pdf), are:
 *      convertFilesToPS()
 *      convertFilesFittedToPS()
 *      convertSegmentedPagesToPS()
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "allheaders.h"

/* --------------------------------------------*/
#if  USE_PSIO   /* defined in environ.h */
 /* --------------------------------------------*/

/*-------------------------------------------------------------*
 *                Convert files in a directory to PS           *
 *-------------------------------------------------------------*/
/*
 *  convertFilesToPS()
 *
 *      Input:  dirin (input directory)
 *              substr (<optional> substring filter on filenames; can be NULL)
 *              res (typ. 300 or 600 ppi)
 *              fileout (output ps file)
 *      Return: 0 if OK, 1 on error
 *
 *  Notes:
 *      (1) This generates a PS file for all image files in a specified
 *          directory that contain the substr pattern to be matched.
 *      (2) Each image is written to a separate page in the output PS file.
 *      (3) All images are written compressed:
 *              * if tiffg4  -->  use ccittg4
 *              * if jpeg    -->  use dct
 *              * all others -->  use flate
 *          If the image is jpeg or tiffg4, we use the existing compressed
 *          strings for the encoding; otherwise, we read the image into
 *          a pix and flate-encode the pieces.
 *      (4) The resolution is often confusing.  It is interpreted
 *          as the resolution of the output display device:  "If the
 *          input image were digitized at 300 ppi, what would it
 *          look like when displayed at res ppi."  So, for example,
 *          if res = 100 ppi, then the display pixels are 3x larger
 *          than the 300 ppi pixels, and the image will be rendered
 *          3x larger.
 *      (5) The size of the PostScript file is independent of the resolution,
 *          because the entire file is encoded.  The res parameter just
 *          tells the PS decomposer how to render the page.  Therefore,
 *          for minimum file size without loss of visual information,
 *          if the output res is less than 300, you should downscale
 *          the image to the output resolution before wrapping in PS.
 *      (6) The "canvas" on which the image is rendered, at the given
 *          output resolution, is a standard page size (8.5 x 11 in).
 */
l_int32
convertFilesToPS(const char  *dirin,
                 const char  *substr,
                 l_int32      res,
                 const char  *fileout)
{
SARRAY  *sa;

    PROCNAME("convertFilesToPS");

    if (!dirin)
        return ERROR_INT("dirin not defined", procName, 1);
    if (!fileout)
        return ERROR_INT("fileout not defined", procName, 1);
    if (res <= 0) {
        L_INFO("setting res to 300 ppi", procName);
        res = 300;
    }
    if (res < 10 || res > 4000)
        L_WARNING("res is typically in the range 300-600 ppi", procName);

        /* Get all filtered and sorted full pathnames. */
    sa = getSortedPathnamesInDirectory(dirin, substr, 0, 0);

        /* Generate the PS file. */
    sarrayConvertFilesToPS(sa, res, fileout);
    sarrayDestroy(&sa);
    return 0;
}


/*
 *  sarrayConvertFilesToPS()
 *
 *      Input:  sarray (of full path names)
 *              res (typ. 300 or 600 ppi)
 *              fileout (output ps file)
 *      Return: 0 if OK, 1 on error
 *
 *  Notes:
 *      (1) See convertFilesToPS()
 */
l_int32
sarrayConvertFilesToPS(SARRAY      *sa,
                       l_int32      res,
                       const char  *fileout)
{
char    *fname;
l_int32  i, nfiles, index, firstfile, ret, format;

    PROCNAME("sarrayConvertFilesToPS");

    if (!sa)
        return ERROR_INT("sa not defined", procName, 1);
    if (!fileout)
        return ERROR_INT("fileout not defined", procName, 1);
    if (res <= 0) {
        L_INFO("setting res to 300 ppi", procName);
        res = 300;
    }
    if (res < 10 || res > 4000)
        L_WARNING("res is typically in the range 300-600 ppi", procName);

    nfiles = sarrayGetCount(sa);
    firstfile = TRUE;
    for (i = 0, index = 0; i < nfiles; i++) {
        fname = sarrayGetString(sa, i, L_NOCOPY);
        ret = pixReadHeader(fname, &format, NULL, NULL, NULL, NULL, NULL);
        if (ret) continue;
        if (format == IFF_UNKNOWN)
            continue;

        writeImageCompressedToPSFile(fname, fileout, res, &firstfile, &index);
    }

    return 0;
}


/*
 *  convertFilesFittedToPS()
 *
 *      Input:  dirin (input directory)
 *              substr (<optional> substring filter on filenames; can be NULL)
 *              xpts, ypts (desired size in printer points; use 0 for default)
 *              fileout (output ps file)
 *      Return: 0 if OK, 1 on error
 *
 *  Notes:
 *      (1) This generates a PS file for all files in a specified directory
 *          that contain the substr pattern to be matched.
 *      (2) Each image is written to a separate page in the output PS file.
 *      (3) All images are written compressed:
 *              * if tiffg4  -->  use ccittg4
 *              * if jpeg    -->  use dct
 *              * all others -->  use flate
 *          If the image is jpeg or tiffg4, we use the existing compressed
 *          strings for the encoding; otherwise, we read the image into
 *          a pix and flate-encode the pieces.
 *      (4) The resolution is internally determined such that the images
 *          are rendered, in at least one direction, at 100% of the given
 *          size in printer points.  Use 0.0 for xpts or ypts to get
 *          the default value, which is 612.0 or 792.0, rsp.
 *      (5) The size of the PostScript file is independent of the resolution,
 *          because the entire file is encoded.  The @xpts and @ypts
 *          parameter tells the PS decomposer how to render the page.
 */
l_int32
convertFilesFittedToPS(const char  *dirin,
                       const char  *substr,
                       l_float32    xpts,
                       l_float32    ypts,
                       const char  *fileout)
{
SARRAY  *sa;

    PROCNAME("convertFilesFittedToPS");

    if (!dirin)
        return ERROR_INT("dirin not defined", procName, 1);
    if (!fileout)
        return ERROR_INT("fileout not defined", procName, 1);
    if (xpts <= 0.0) {
        L_INFO("setting xpts to 612.0 ppi", procName);
        xpts = 612.0;
    }
    if (ypts <= 0.0) {
        L_INFO("setting ypts to 792.0 ppi", procName);
        ypts = 792.0;
    }
    if (xpts < 100.0 || xpts > 2000.0 || ypts < 100.0 || ypts > 2000.0)
        L_WARNING("xpts,ypts are typically in the range 500-800", procName);

        /* Get all filtered and sorted full pathnames. */
    sa = getSortedPathnamesInDirectory(dirin, substr, 0, 0);

        /* Generate the PS file. */
    sarrayConvertFilesFittedToPS(sa, xpts, ypts, fileout);
    sarrayDestroy(&sa);
    return 0;
}


/*
 *  sarrayConvertFilesFittedToPS()
 *
 *      Input:  sarray (of full path names)
 *              xpts, ypts (desired size in printer points; use 0 for default)
 *              fileout (output ps file)
 *      Return: 0 if OK, 1 on error
 *
 *  Notes:
 *      (1) See convertFilesFittedToPS()
 */
l_int32
sarrayConvertFilesFittedToPS(SARRAY      *sa,
                             l_float32    xpts,
                             l_float32    ypts,
                             const char  *fileout)
{
char    *fname;
l_int32  ret, i, w, h, nfiles, index, firstfile, format, res;

    PROCNAME("sarrayConvertFilesFittedToPS");

    if (!sa)
        return ERROR_INT("sa not defined", procName, 1);
    if (!fileout)
        return ERROR_INT("fileout not defined", procName, 1);
    if (xpts <= 0.0) {
        L_INFO("setting xpts to 612.0", procName);
        xpts = 612.0;
    }
    if (ypts <= 0.0) {
        L_INFO("setting ypts to 792.0", procName);
        ypts = 792.0;
    }
    if (xpts < 100.0 || xpts > 2000.0 || ypts < 100.0 || ypts > 2000.0)
        L_WARNING("xpts,ypts are typically in the range 500-800", procName);

    nfiles = sarrayGetCount(sa);
    firstfile = TRUE;
    for (i = 0, index = 0; i < nfiles; i++) {
        fname = sarrayGetString(sa, i, L_NOCOPY);
        ret = pixReadHeader(fname, &format, &w, &h, NULL, NULL, NULL);
        if (ret) continue;
        if (format == IFF_UNKNOWN)
            continue;

            /* Be sure the entire image is wrapped */
        if (xpts * h < ypts * w)
            res = (l_int32)((l_float32)w * 72.0 / xpts);
        else
            res = (l_int32)((l_float32)h * 72.0 / ypts);

        writeImageCompressedToPSFile(fname, fileout, res, &firstfile, &index);
    }

    return 0;
}


/*
 *  writeImageCompressedToPSFile()
 *
 *      Input:  filein (input image file)
 *              fileout (output ps file)
 *              res (output printer resolution)
 *              &firstfile (<input and return> 1 if the first image;
 *                          0 otherwise)
 *              &index (<input and return> index of image in output ps file)
 *      Return: 0 if OK, 1 on error
 *
 *  Notes:
 *      (1) This wraps a single page image in PS.
 *      (2) The input file can be in any format.  It is compressed as follows:
 *             * if in tiffg4  -->  use ccittg4
 *             * if in jpeg    -->  use dct
 *             * all others    -->  use flate
 *      (3) @index is incremented if the page is successfully written.
 */
l_int32
writeImageCompressedToPSFile(const char  *filein,
                             const char  *fileout,
                             l_int32      res,
                             l_int32     *pfirstfile,
                             l_int32     *pindex)
{
const char  *op;
l_int32      format, retval;
FILE        *fp;

    PROCNAME("writeImageCompressedToPSFile");

    if (!pfirstfile || !pindex)
        return ERROR_INT("&firstfile and &index not defined", procName, 1);

    if ((fp = fopenReadStream(filein)) == NULL)
        return ERROR_INT("filein not found", procName, 1);
    findFileFormat(fp, &format);
    fclose(fp);
    if (format == IFF_UNKNOWN) {
        L_ERROR_STRING("Format of %s not known", procName, filein);
        return 1;
    }

    op = (*pfirstfile == TRUE) ? "w" : "a";
    if (format == IFF_JFIF_JPEG) {
        retval = convertJpegToPS(filein, fileout, op, 0, 0,
                                 res, 1.0, *pindex + 1, TRUE);
        if (retval == 0) {
            *pfirstfile = FALSE;
            (*pindex)++;
        }
    }
    else if (format == IFF_TIFF_G4) {
        retval = convertTiffG4ToPS(filein, fileout, op, 0, 0,
                                   res, 1.0, *pindex + 1, FALSE, TRUE);
        if (retval == 0) {
            *pfirstfile = FALSE;
            (*pindex)++;
        }
    }
    else {  /* all other image formats */
        retval = convertFlateToPS(filein, fileout, op, 0, 0,
                                  res, 1.0, *pindex + 1, TRUE);
        if (retval == 0) {
            *pfirstfile = FALSE;
            (*pindex)++;
        }
    }

    return retval;
}


/*-------------------------------------------------------------*
 *              Convert mixed text/image files to PS           *
 *-------------------------------------------------------------*/
/*
 *  convertSegmentedPagesToPS()
 *
 *      Input:  pagedir (input page image directory)
 *              pagestr (<optional> substring filter on page filenames;
 *                       can be NULL)
 *              maskdir (input mask image directory)
 *              maskstr (<optional> substring filter on mask filenames;
 *                       can be NULL)
 *              numpre (number of characters in name before number)
 *              numpost (number of characters in name after number)
 *              maxnum (only consider page numbers up to this value)
 *              textscale (scale of text output relative to pixs)
 *              imagescale (scale of image output relative to pixs)
 *              threshold (for binarization; typ. about 190; 0 for default)
 *              fileout (output ps file)
 *      Return: 0 if OK, 1 on error
 *
 *  Notes:
 *      (1) This generates a PS file for all page image and mask files in two
 *          specified directories and that contain the page numbers as
 *          specified below.  The two directories can be the same, in which
 *          case the page and mask files are differentiated by the two
 *          substrings for string matches.
 *      (2) The page images are taken in lexicographic order.
 *          Mask images whose numbers match the page images are used to
 *          segment the page images.  Page images without a matching 
 *          mask image are scaled, thresholded and rendered entirely as text.
 *      (3) Each PS page is generated as a compressed representation of
 *          the page image, where the part of the image under the mask
 *          is suitably scaled and compressed as DCT (i.e., jpeg), and
 *          the remaining part of the page is suitably scaled, thresholded,
 *          compressed as G4 (i.e., tiff g4), and rendered by painting
 *          black through the resulting text mask.
 *      (4) The scaling is typically 2x down for the DCT component
 *          (@imagescale = 0.5) and 2x up for the G4 component
 *          (@textscale = 2.0).
 *      (5) The resolution is automatically set to fit to a
 *          letter-size (8.5 x 11 inch) page.
 *      (6) Both the DCT and the G4 encoding are PostScript level 2.
 *      (7) It is assumed that the page number is contained within
 *          the basename (the filename without directory or extension).
 *          @numpre is the number of characters in the basename
 *          preceeding the actual page numer; @numpost is the number
 *          following the page number.  Note: the same numbers must be
 *          applied to both the page and mask image names.
 *      (8) To render a page as is -- that is, with no thresholding
 *          of any pixels -- use a mask in the mask directory that is
 *          full size with all pixels set to 1.  If the page is 1 bpp,
 *          it is not necessary to have a mask.
 */
l_int32
convertSegmentedPagesToPS(const char  *pagedir,
                          const char  *pagestr,
                          const char  *maskdir,
                          const char  *maskstr,
                          l_int32      numpre,
                          l_int32      numpost,
                          l_int32      maxnum,
                          l_float32    textscale,
                          l_float32    imagescale,
                          l_int32      threshold,
                          const char  *fileout)
{
l_int32  pageno, i, npages;
PIX     *pixs, *pixm;
SARRAY  *sapage, *samask;

    PROCNAME("convertSegmentedPagesToPS");

    if (!pagedir)
        return ERROR_INT("pagedir not defined", procName, 1);
    if (!maskdir)
        return ERROR_INT("maskdir not defined", procName, 1);
    if (!fileout)
        return ERROR_INT("fileout not defined", procName, 1);
    if (threshold <= 0) {
        L_INFO("setting threshold to 190", procName);
        threshold = 190;
    }

        /* Get numbered full pathnames; max size of sarray is maxnum */
    sapage = getNumberedPathnamesInDirectory(pagedir, pagestr,
                                             numpre, numpost, maxnum);
    samask = getNumberedPathnamesInDirectory(maskdir, maskstr,
                                             numpre, numpost, maxnum);
    sarrayPadToSameSize(sapage, samask, (char *)"");
    if ((npages = sarrayGetCount(sapage)) == 0) {
        sarrayDestroy(&sapage);
        sarrayDestroy(&samask);
        return ERROR_INT("no matching pages found", procName, 1);
    }

        /* Generate the PS file */
    pageno = 1;
    for (i = 0; i < npages; i++) {
        if ((pixs = pixReadIndexed(sapage, i)) == NULL)
            continue;
        pixm = pixReadIndexed(samask, i);
        pixWriteSegmentedPageToPS(pixs, pixm, textscale, imagescale,
                                  threshold, pageno, fileout);
        pixDestroy(&pixs);
        pixDestroy(&pixm);
        pageno++;
    }

    sarrayDestroy(&sapage);
    sarrayDestroy(&samask);
    return 0;
}


/*
 *  pixWriteSegmentedPageToPS()
 *
 *      Input:  pixs (all depths; colormap ok)
 *              pixm (<optional> 1 bpp segmentation mask over image region)
 *              textscale (scale of text output relative to pixs)
 *              imagescale (scale of image output relative to pixs)
 *              threshold (threshold for binarization; typ. 190)
 *              pageno (page number in set; use 1 for new output file)
 *              fileout (output ps file)
 *      Return: 0 if OK, 1 on error
 *
 *  Notes:
 *      (1) This generates the PS string for a mixed text/image page,
 *          and adds it to an existing file if @pageno > 1.
 *          The PS output is determined by fitting the result to
 *          a letter-size (8.5 x 11 inch) page.
 *      (2) The two images (pixs and pixm) are at the same resolution
 *          (typically 300 ppi).  They are used to generate two compressed
 *          images, pixb and pixc, that are put directly into the output
 *          PS file.
 *      (3) pixb is the text component.  In the PostScript world, we think of
 *          it as a mask through which we paint black.  It is produced by
 *          scaling pixs by @textscale, and thresholding to 1 bpp.
 *      (4) pixc is the image component, which is that part of pixs under
 *          the mask pixm.  It is scaled from pixs by @imagescale.
 *      (5) Typical values are textscale = 2.0 and imagescale = 0.5.
 *      (6) If pixm == NULL, the page has only text.  If it is all black,
 *          the page is all image and has no text.
 *      (7) This can be used to write a multi-page PS file, by using
 *          sequential page numbers with the same output file.  It can
 *          also be used to write separate PS files for each page,
 *          by using different output files with @pageno = 0 or 1.
 */
l_int32
pixWriteSegmentedPageToPS(PIX         *pixs,
                          PIX         *pixm,
                          l_float32    textscale,
                          l_float32    imagescale,
                          l_int32      threshold,
                          l_int32      pageno,
                          const char  *fileout)
{
l_int32    alltext, notext, d, ret;
l_uint32   val;
l_float32  scaleratio;
PIX       *pixmi, *pixmis, *pixt, *pixg, *pixsc, *pixb, *pixc;

    PROCNAME("pixWriteSegmentedPageToPS");

    if (!pixs)
        return ERROR_INT("pixs not defined", procName, 1);
    if (!fileout)
        return ERROR_INT("fileout not defined", procName, 1);
    if (imagescale <= 0.0 || textscale <= 0.0)
        return ERROR_INT("relative scales must be > 0.0", procName, 1);

        /* Analyze the page.  Determine the ratio by which the
         * binary text mask is scaled relative to the image part.
         * If there is no image region (alltext == TRUE), the
         * text mask will be rendered directly to fit the page,
         * and scaleratio = 1.0.  */
    alltext = TRUE;
    notext = FALSE;
    scaleratio = 1.0;
    if (pixm) {
        pixZero(pixm, &alltext);  /* pixm empty: all text */
        if (alltext)
            pixm = NULL;  /* treat it as not existing here */
        else {
            pixmi = pixInvert(NULL, pixm);
            pixZero(pixmi, &notext);  /* pixm full; no text */
            pixDestroy(&pixmi);
            scaleratio = textscale / imagescale;
        }
    }

    if (pixGetDepth(pixs) == 1) {  /* render tiff g4 */
        pixb = pixClone(pixs);
        pixc = NULL;
    }
    else {
        pixt = pixConvertTo8Or32(pixs, 0, 0);  /* this can be a clone of pixs */

            /* Get the binary text mask.  Note that pixg cannot be a
             * clone of pixs, because it may be altered by pixSetMasked(). */
        pixb = NULL;
        if (notext == FALSE) {
            d = pixGetDepth(pixt);
            if (d == 8)
                pixg = pixCopy(NULL, pixt);
            else  /* d == 32 */
                pixg = pixConvertRGBToLuminance(pixt);
            if (pixm)  /* clear out the image parts */
                pixSetMasked(pixg, pixm, 255);
            if (textscale == 1.0)
                pixsc = pixClone(pixg);
            else if (textscale >= 0.7)
                pixsc = pixScaleGrayLI(pixg, textscale, textscale);
            else
                pixsc = pixScaleAreaMap(pixg, textscale, textscale);
            pixb = pixThresholdToBinary(pixsc, threshold);
            pixDestroy(&pixg);
            pixDestroy(&pixsc);
        }

            /* Get the scaled image region */
        pixc = NULL;
        if (pixm) {
            if (imagescale == 1.0)
                pixsc = pixClone(pixt);  /* can possibly be a clone of pixs */
            else
                pixsc = pixScale(pixt, imagescale, imagescale);

                /* If pixm is not full, clear the pixels in pixsc
                 * corresponding to bg in pixm, where there can be text
                 * that is written through the mask pixb.  Note that
                 * we could skip this and use pixsc directly in
                 * pixWriteMixedToPS(); however, clearing these
                 * non-image regions to a white background will reduce
                 * the size of pixc (relative to pixsc), and hence
                 * reduce the size of the PS file that is generated.
                 * Use a copy so that we don't accidentally alter pixs.  */
            if (notext == FALSE) {
                pixmis = pixScale(pixm, imagescale, imagescale);
                pixmi = pixInvert(NULL, pixmis);
                val = (d == 8) ? 0xff : 0xffffff00;
                pixc = pixCopy(NULL, pixsc);
                pixSetMasked(pixc, pixmi, val);  /* clear non-image part */
                pixDestroy(&pixmis);
                pixDestroy(&pixmi);
            }
            else
                pixc = pixClone(pixsc);
            pixDestroy(&pixsc);
        }
        pixDestroy(&pixt);
    }

    ret = pixWriteMixedToPS(pixb, pixc, scaleratio, pageno, fileout);
    pixDestroy(&pixb);
    pixDestroy(&pixc);
    return ret;
}


/*
 *  pixWriteMixedToPS()
 *
 *      Input:  pixb (<optionall> 1 bpp "mask"; typically for text)
 *              pixc (<optional> 8 or 32 bpp image regions)
 *              scale (relative scale factor for rendering pixb
 *                    relative to pixc; typ. 4.0)
 *              pageno (page number in set; use 1 for new output file)
 *              fileout (output ps file)
 *      Return: 0 if OK, 1 on error
 *
 *  Notes:
 *      (1) This low level function generates the PS string for a mixed
 *          text/image page, and adds it to an existing file if
 *          @pageno > 1.
 *      (2) The two images (pixb and pixc) are typically generated at the
 *          resolution that they will be rendered in the PS file.
 *      (3) pixb is the text component.  In the PostScript world, we think of
 *          it as a mask through which we paint black.
 *      (4) pixc is the (typically halftone) image component.  It is
 *          white in the rest of the page.  To minimize the size of the
 *          PS file, it should be rendered at a resolution that is at
 *          least equal to its actual resolution.
 *      (5) @scale gives the ratio of resolution of pixb to pixc.
 *          Typical resolutions are: 600 ppi for pixb, 150 ppi for pixc;
 *          so @scale = 4.0.  If one of the images is not defined,
 *          the value of @scale is ignored.
 *      (6) We write pixc with DCT compression (jpeg).  This is followed
 *          by painting the text as black through the mask pixb.  If
 *          pixc doesn't exist (alltext), we write the text with the
 *          PS "image" operator instead of the "imagemask" operator,
 *          because ghostscript's ps2pdf is flaky when the latter is used.
 *      (7) The actual output resolution is determined by fitting the
 *          result to a letter-size (8.5 x 11 inch) page.
 */
l_int32
pixWriteMixedToPS(PIX         *pixb,
                  PIX         *pixc,
                  l_float32    scale,
                  l_int32      pageno,
                  const char  *fileout)
{
const char   tnameb[] = "/tmp/junk_pix_write_mixed.tif";
const char   tnamec[] = "/tmp/junk_pix_write_mixed.jpg";
const char  *op;
l_int32      resb, resc, endpage, maskop, ret;

    PROCNAME("pixWriteMixedToPS");

    if (!pixb && !pixc)
        return ERROR_INT("pixb and pixc both undefined", procName, 1);
    if (!fileout)
        return ERROR_INT("fileout not defined", procName, 1);

        /* Compute the resolution that fills a letter-size page. */
    if (!pixc)
       resb = getResLetterPage(pixGetWidth(pixb), pixGetHeight(pixb), 0);
    else {
       resc = getResLetterPage(pixGetWidth(pixc), pixGetHeight(pixc), 0);
       if (pixb)
           resb = (l_int32)(scale * resc);
    }

        /* Write the jpeg image first */
    if (pixc) {
        pixWrite(tnamec, pixc, IFF_JFIF_JPEG);
        endpage = (pixb) ? FALSE : TRUE;
        op = (pageno <= 1) ? "w" : "a";
        ret = convertJpegToPS(tnamec, fileout, op, 0, 0, resc, 1.0,
                              pageno, endpage);
        if (ret)
            return ERROR_INT("jpeg data not written", procName, 1);
    }

        /* Write the binary data, either directly or, if there is
         * a jpeg image on the page, through the mask. */
    if (pixb) {
        pixWrite(tnameb, pixb, IFF_TIFF_G4);
        op = (pageno <= 1 && !pixc) ? "w" : "a";
        maskop = (pixc) ? 1 : 0;
        ret = convertTiffG4ToPS(tnameb, fileout, op, 0, 0, resb, 1.0,
              pageno, maskop, 1);
        if (ret)
            return ERROR_INT("tiff data not written", procName, 1);
    }

    return 0;
}


/*-------------------------------------------------------------*
 *            Convert any image file to PS for embedding       *
 *-------------------------------------------------------------*/
/*
 *  convertToPSEmbed()
 *
 *      Input:  filein (input image file -- any format)
 *              fileout (output ps file)
 *              level (compression: 1 (uncompressed), 2 or 3)
 *      Return: 0 if OK, 1 on error
 *
 *  Notes:
 *      (1) This is a wrapper function that generates a PS file with
 *          a bounding box, from any input image file.
 *      (2) Do the best job of compression given the specified level.
 *          @level=3 does flate compression on anything that is not
 *          tiffg4 (1 bpp) or jpeg (8 bpp or rgb).
 *      (3) If @level=2 and the file is not tiffg4 or jpeg, it will
 *          first be written to file as jpeg with quality = 75.
 *          This will remove the colormap and cause some degradation
 *          in the image.
 *      (4) The bounding box is required when a program such as TeX
 *          (through epsf) places and rescales the image.  It is
 *          sized for fitting the image to an 8.5 x 11.0 inch page.
 */
l_int32
convertToPSEmbed(const char  *filein,
                 const char  *fileout,
                 l_int32      level)
{
const char  nametif[] = "/tmp/junk_convert_ps_embed.tif";
const char  namejpg[] = "/tmp/junk_convert_ps_embed.jpg";
l_int32     d, format;
FILE       *fp;
PIX        *pix, *pixs;

    PROCNAME("convertToPSEmbed");

    if (!filein)
        return ERROR_INT("filein not defined", procName, 1);
    if (!fileout)
        return ERROR_INT("fileout not defined", procName, 1);
    if (level != 1 && level != 2 && level != 3) {
        L_ERROR("invalid level specified; using level 2", procName);
        level = 2;
    }

    if (level == 1) {  /* no compression */
        pixWritePSEmbed(filein, fileout);
        return 0;
    }

        /* Find the format and write out directly if in jpeg or tiff g4 */
    if ((fp = fopen(filein, "rb")) == NULL)
        return ERROR_INT("filein not found", procName, 1);
    findFileFormat(fp, &format);
    fclose(fp);
    if (format == IFF_JFIF_JPEG) {
        convertJpegToPSEmbed(filein, fileout);
        return 0;
    }
    else if (format == IFF_TIFF_G4) {
        convertTiffG4ToPSEmbed(filein, fileout);
        return 0;
    }

        /* If level 3, flate encode. */
    if (level == 3) {
        convertFlateToPSEmbed(filein, fileout);
        return 0;
    }

        /* OK, it's level 2, so we must convert to jpeg or tiff g4 */
    if ((pixs = pixRead(filein)) == NULL)
        return ERROR_INT("image not read from file", procName, 1);
    d = pixGetDepth(pixs);
    if ((d == 2 || d == 4) && !pixGetColormap(pixs))
        pix = pixConvertTo8(pixs, 0);
    else if (d == 16)
        pix = pixConvert16To8(pixs, 1);
    else
        pix = pixRemoveColormap(pixs, REMOVE_CMAP_BASED_ON_SRC);

    d = pixGetDepth(pix);
    if (d == 1) {
        pixWrite(nametif, pix, IFF_TIFF_G4);
        convertTiffG4ToPSEmbed(nametif, fileout);
    }
    else {
        pixWrite(namejpg, pix, IFF_JFIF_JPEG);
        convertJpegToPSEmbed(namejpg, fileout);
    }

    pixDestroy(&pix);
    pixDestroy(&pixs);
    return 0;
}

/* --------------------------------------------*/
#endif  /* USE_PSIO */
/* --------------------------------------------*/

