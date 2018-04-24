/*
Mayher Sandhu
mxs163430
SE3377.501
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
#define MATRIX_NAME_STRING "Matrix"

using namespace std;

const int maxRecordStringLength=25;

//class for Binary File Record
class BinaryFileRecord
{
public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
};
//class for Binary File Header
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

  //initialize the BinaryFileHeader and BinaryFileRecord
  BinaryFileHeader *binaryHeader=new BinaryFileHeader();
  BinaryFileRecord *binaryRecord=new BinaryFileRecord();

  //read the BinaryFileHeader
  binInfile.read((char *) binaryHeader, sizeof(BinaryFileHeader));

  //intialize the strings for the cells in matrix
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

  //use stringstreams to get each value
  
  //getting magic Number
  stringstream convertMagic;
  convertMagic << hex << uppercase << binaryHeader->magicNumber;
  magicNo += convertMagic.str();

  //getting the version number
  stringstream convertVersion;
  convertVersion << hex << binaryHeader->versionNumber;
  version+=convertVersion.str();

  //getting the number of records
  stringstream convertNumRec;
  convertNumRec << binaryHeader->numRecords;
  numRecords+=convertNumRec.str();

  //getting the first string
  binInfile.read((char *) binaryRecord, sizeof(BinaryFileRecord));
  stringstream convertString1;
  convertString1 << binaryRecord->stringBuffer;
  string1+=convertString1.str();
  //getting the length of first string
  stringstream stringLength1;
  stringLength1 << string1.length();
  strlen1+=stringLength1.str();

  //getting the second string
  binInfile.read((char *) binaryRecord, sizeof(BinaryFileRecord));
  stringstream convertString2;
  convertString2 << binaryRecord->stringBuffer;
  string2+=convertString2.str();
  //getting the length of the second string
  stringstream stringLength2;
  stringLength2 << string2.length();
  strlen2+=stringLength2.str();

  //getting the third string
  binInfile.read((char *) binaryRecord, sizeof(BinaryFileRecord));
  stringstream convertString3;
  convertString3 << binaryRecord->stringBuffer;
  string3+=convertString3.str();
  //getting the length of the third string
  stringstream stringLength3;
  stringLength3 << string3.length();
  strlen3+=stringLength3.str();

  //getting the fourth string
  binInfile.read((char *) binaryRecord, sizeof(BinaryFileRecord));
  stringstream convertString4;
  convertString4 << binaryRecord->stringBuffer;
  string4+=convertString4.str();
  //getting the length of the fourth string
  stringstream stringLength4;
  stringLength4 << string4.length();
  strlen4+=stringLength4.str();

  //setting each matrix cell to the input read in above
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

  //draw the matrix
  drawCDKMatrix(myMatrix, true);    /* required  */

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
