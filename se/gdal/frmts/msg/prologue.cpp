/******************************************************************************
 * $Id: prologue.cpp 15064 2008-07-28 19:10:23Z mloskot $
 *
 * Purpose:  Implementation of Prologue class. Parse the prologue of one
 *           repeat cycle and keep the interesting info.
 * Author:   Bas Retsios, retsios@itc.nl
 *
 ******************************************************************************
 * Copyright (c) 2004, ITC
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ******************************************************************************/

#include "prologue.h"

int size_SatelliteStatus()
{
  int iSizePrimary = 1+4+1+1+4+4+1+1+4+4+1;;

  int iSizeOrbitCoef = 4 + 4 + 8*8 + 8*8 + 8*8 + 8*8 + 8*8 + 8*8;
  int iSizeOrbit = 4 + 4 + 100*iSizeOrbitCoef;
  int iSizeAttitudeCoef = 4 + 4 + 8*8 + 8*8 + 8*8;
  int iSizeAttitude = 4 + 4 + 8 + 100*iSizeAttitudeCoef;
  int iSizeSpinRateatRCStart = 8;
  int iSizeUTCCorrelation = 4 + 4 + 4*4*3 + 8 + 8 + 8 + 8 + 8;
  
  int iTotalSize = iSizePrimary + iSizeOrbit + iSizeAttitude + iSizeSpinRateatRCStart + iSizeUTCCorrelation;

  return iTotalSize;
}

int size_ImageAcquisition()
{
  // up to  DHSSSynchSelection
  int iSize1 = 8 + 8 + 8 + 12 + 42 + 42*2 + 2 + 2 + 2 + 2 + 1;
  // up to RefocusingDirection
  int iSize2 = 42*2 + 42 + 42*2 + 42*2 + 42*2 + 27*2 + 15*2 + 6*2 + 1 + 2 + 1;
  // to end
  int iSize3 = 2 + 1 + 2 + 4 + 2 + 2 + 2 + 1 + 4 + 1 + 4 + 4 + 1 + 1 + 2 + 2 + 2 + 2;
    
  int iTotalSize = iSize1 + iSize2 + iSize3;

  return iTotalSize;
}

int size_CelestialEvents()
{
  int iSizeCelestialBodies = 2 + 2 + 4 + 4 + 3*100*(2 + 2 + 8*8 + 8*8) + 100*(20*(2 + 2 + 2 + 8*8 + 8*8));

  int iSizeRelationToImage = 1 + 2 + 2 + 1 + 1 + 1;
    
  int iTotalSize = iSizeCelestialBodies + iSizeRelationToImage;

  return iTotalSize;
}

int size_Correction()
{
  return 19229;
}

double iReadDouble(std::ifstream & ifile)
{
  // will use 8 bytes from the file to read a DOUBLE (according to the MSG definition of DOUBLE)
    unsigned char buf [8];
    
    ifile.read((char*)buf, 8);
    double rVal;
    ((char*)(&rVal))[0] = buf[7];
    ((char*)(&rVal))[1] = buf[6];
    ((char*)(&rVal))[2] = buf[5];
    ((char*)(&rVal))[3] = buf[4];
    ((char*)(&rVal))[4] = buf[3];
    ((char*)(&rVal))[5] = buf[2];
    ((char*)(&rVal))[6] = buf[1];
    ((char*)(&rVal))[7] = buf[0];
    
    return rVal;
}

double iReadReal(std::ifstream & ifile)
{
  // will use 4 bytes from the file to read a REAL (according to the MSG definition of REAL)
    unsigned char buf [4];
    
    ifile.read((char*)buf, 4);
    float rVal;
    ((char*)(&rVal))[0] = buf[3];
    ((char*)(&rVal))[1] = buf[2];
    ((char*)(&rVal))[2] = buf[1];
    ((char*)(&rVal))[3] = buf[0];
    
    return rVal;
}

int iReadInt(std::ifstream & ifile)
{
  // will use 4 bytes from the file to read an int (according to the MSG definition of int)
    unsigned char buf [4];
    
    ifile.read((char*)buf, 4);
    int iResult = (buf[0]<<24)+(buf[1]<<16)+(buf[2]<<8)+buf[3];

    return iResult;
}

unsigned char iReadByte (std::ifstream & ifile)
{
  // will read 1 byte from the file
    char b;
    
    ifile.read(&b, 1);

    return b;
}

ReferenceGridRecord::ReferenceGridRecord(std::ifstream & ifile)
{
    NumberOfLines = iReadInt(ifile);
    NumberOfColumns = iReadInt(ifile);
    LineDirGridStep = iReadReal(ifile);
    ColumnDirGridStep = iReadReal(ifile);
    GridOrigin = iReadByte(ifile);
}

PlannedCoverageVIS_IRRecord::PlannedCoverageVIS_IRRecord(std::ifstream & ifile)
{
    SouthernLinePlanned = iReadInt(ifile);
    NorthernLinePlanned = iReadInt(ifile);
    EasternColumnPlanned = iReadInt(ifile);
    WesternColumnPlanned = iReadInt(ifile);
}

PlannedCoverageHRVRecord::PlannedCoverageHRVRecord(std::ifstream & ifile)
{
    LowerSouthLinePlanned = iReadInt(ifile);
    LowerNorthLinePlanned = iReadInt(ifile);
    LowerEastColumnPlanned = iReadInt(ifile);
    LowerWestColumnPlanned = iReadInt(ifile);
    UpperSouthLinePlanned = iReadInt(ifile);
    UpperNorthLinePlanned = iReadInt(ifile);
    UpperEastColumnPlanned = iReadInt(ifile);
    UpperWestColumnPlanned = iReadInt(ifile);
}


ImageDescriptionRecord::ImageDescriptionRecord(std::ifstream & ifile)
{
    TypeOfProjection = iReadByte(ifile);
    LongitudeOfSSP = iReadReal(ifile);
    ReferenceGridVIS_IR = new ReferenceGridRecord(ifile);
    ReferenceGridHRV = new ReferenceGridRecord(ifile);
    PlannedCoverageVIS_IR = new PlannedCoverageVIS_IRRecord(ifile);
    PlannedCoverageHRV = new PlannedCoverageHRVRecord(ifile);
    ImageProcDirection = iReadByte(ifile);
    PixelGenDirection = iReadByte(ifile);
    for (int i=0; i < 12; ++i)
      PlannedChannelProcessing[i] = iReadByte(ifile);
}

ImageDescriptionRecord::~ImageDescriptionRecord()
{
    delete ReferenceGridVIS_IR;
    delete ReferenceGridHRV;
    delete PlannedCoverageVIS_IR;
    delete PlannedCoverageHRV;
}

RadiometricProcessingRecord::RadiometricProcessingRecord(std::ifstream & ifile)
{
  // skip a part that doesn't interest us
    unsigned char dummy [12];
    int i;
    for (i = 0; i < 6; ++i)
      ifile.read((char*)dummy, 12);

    for (i = 0; i < 12; ++i)
    {
      Cal_Slope[i] = iReadDouble(ifile);
      Cal_Offset[i] = iReadDouble(ifile);
    }
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Prologue::Prologue()
: m_idr(0)
, m_rpr(0)
{

}

Prologue::~Prologue()
{
  if (m_idr)
    delete m_idr;
  if (m_rpr)
    delete m_rpr;
}

void Prologue::read(std::ifstream & ifile)
{
  unsigned char version = iReadByte(ifile);

  int iSkipHeadersSize = size_SatelliteStatus() + size_ImageAcquisition() + size_CelestialEvents() + size_Correction();

#if _MSC_VER > 1000 && _MSC_VER < 1300
  ifile.seekg(iSkipHeadersSize, std::ios_base::seekdir::cur);
#else
  ifile.seekg(iSkipHeadersSize, std::ios_base::cur);
#endif

  m_idr = new ImageDescriptionRecord(ifile);

  m_rpr = new RadiometricProcessingRecord(ifile);
  // TODO: file is not left at the end of the Radiometric Processing Record
}
