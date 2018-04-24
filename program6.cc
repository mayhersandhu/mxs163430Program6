/*
 * Usage of CDK Matrix
 *
 * File:   example1.cc
 * Author: Stephen Perkins
 * Email:  stephen.perkins@utdallas.edu
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include "cdk.h"
#include <stdint.h>
#include <sstream>

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Test Matrix"

using namespace std;

const int maxRecordStringLength=25;

class BinaryFileRecord
{
public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
};

class BinaryFileHeader
{
public: uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;
};

int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char 		*rowTitles[] = {"R0", "R1", "R2", "R3", "R4", "R5"};
  const char 		*columnTitles[] = {"C0", "C1", "C2", "C3", "C4", "C5"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  ifstream binInfile("cs3377.bin", ios::in | ios::binary);

  BinaryFileHeader *binaryHeader=new BinaryFileHeader();
  BinaryFileRecord *binaryRecord=new BinaryFileRecord();

  binInfile.read((char *) binaryHeader, sizeof(BinaryFileHeader));

  string magicNo="Magic: 0x";
  string version="Version: ";
  string numRecords="NumRecords: ";
  string strlen1="strlen: ";
  string string1="";
  string strlen2="strlen: ";
  string string2="";
  string strlen3="strlen: ";
  string string3;
  string strlen4="strlen: ";
  string string4="";

  stringstream convertMagic;
  convertMagic << hex << uppercase << binaryHeader->magicNumber;
  magicNo += convertMagic.str();

  stringstream convertVersion;
  convertVersion << hex << binaryHeader->versionNumber;
  version+=convertVersion.str();

  stringstream convertNumRec;
  convertNumRec << binaryHeader->numRecords;
  numRecords+=convertNumRec.str();

  binInfile.read((char *) binaryRecord, sizeof(BinaryFileRecord));
  stringstream convertString1;
  convertString1 << binaryRecord->stringBuffer;
  string1+=convertString1.str();
  stringstream stringLength1;
  stringLength1 << string1.length();
  strlen1+=stringLength1.str();

  binInfile.read((char *) binaryRecord, sizeof(BinaryFileRecord));
  stringstream convertString2;
  convertString2 << binaryRecord->stringBuffer;
  string2+=convertString2.str();
  stringstream stringLength2;
  stringLength2 << string2.length();
  strlen2+=stringLength2.str();

  binInfile.read((char *) binaryRecord, sizeof(BinaryFileRecord));
  stringstream convertString3;
  convertString3 << binaryRecord->stringBuffer;
  string3+=convertString3.str();
  stringstream stringLength3;
  stringLength3 << string3.length();
  strlen3+=stringLength3.str();

  binInfile.read((char *) binaryRecord, sizeof(BinaryFileRecord));
  stringstream convertString4;
  convertString4 << binaryRecord->stringBuffer;
  string4+=convertString4.str();
  stringstream stringLength4;
  stringLength4 << string4.length();
  strlen4+=stringLength4.str();

  setCDKMatrixCell(myMatrix, 1, 1, magicNo.c_str());
  setCDKMatrixCell(myMatrix, 1, 2, version.c_str());
  setCDKMatrixCell(myMatrix, 1, 3, numRecords.c_str());
  setCDKMatrixCell(myMatrix, 2, 1, strlen1.c_str());
  setCDKMatrixCell(myMatrix, 2, 2, string1.c_str());
  setCDKMatrixCell(myMatrix, 3, 1, strlen2.c_str());
  setCDKMatrixCell(myMatrix, 3, 2, string2.c_str());
  setCDKMatrixCell(myMatrix, 4, 1, strlen3.c_str());
  setCDKMatrixCell(myMatrix, 4, 2, string3.c_str());
  setCDKMatrixCell(myMatrix, 5, 1, strlen4.c_str());
  setCDKMatrixCell(myMatrix, 5, 2, string4.c_str());

  /*
   * Dipslay a message
   */
  drawCDKMatrix(myMatrix, true);    /* required  */

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
