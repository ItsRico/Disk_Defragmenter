#ifndef DefragRunnerH
#define DefragRunnerH

#include <iostream>
#include <fstream>
using namespace std;

class DiskDrive;
class DiskBlock;

class DiskBlockInfo
{
  unsigned nextBlockID;
  unsigned short fileID;
  unsigned short fileBlockNum;
  friend class DiskDrive;
  friend class DiskBlock;
  void read(ifstream &inf){inf >> fileID >> fileBlockNum >> nextBlockID; }
public:
  DiskBlockInfo(): nextBlockID(0), fileID(0), fileBlockNum(0) {}
}; // class DiskBlockInfo


class DiskBlock
{
  friend class DiskDrive;
  DiskBlockInfo blockInfo;
  char stuff[500];
  DiskBlock(DiskBlockInfo &blockInf) {blockInfo = blockInf;}
public:
  DiskBlock(){}
  unsigned getNext() const  {return blockInfo.nextBlockID;}
  void setNext(unsigned nextBlockID) { blockInfo.nextBlockID = nextBlockID; }
  short getFileBlockNum() const {return blockInfo.fileBlockNum;}
}; // class DiskBlock

class DirectoryEntry
{

  unsigned short fileID;
  unsigned firstBlockID;
  unsigned size;
  friend class DiskDrive;
  void read(istream &inf) {inf >> fileID >> firstBlockID >> size;}
public:
  DirectoryEntry(unsigned short n = 0, unsigned f = 0, int s = 0) : fileID(n),
    firstBlockID(f), size(s){}
  bool operator< (const DirectoryEntry &d)const {return fileID < d.fileID;}
  bool operator== (const DirectoryEntry &d)const {return fileID == d.fileID;}
  DirectoryEntry& operator= (const DirectoryEntry *d){return *this;}
    // prevents cheating by altering original
  void print(ostream &outf) const
    {outf << fileID << ' ' << firstBlockID << ' ' << size << endl;}
  unsigned short getFileID() const {return fileID;}
  unsigned getFirstBlockID() const {return firstBlockID;}
  unsigned getSize() const {return size;}
  void setFirstBlockID(unsigned blockID) {firstBlockID = blockID;}
}; // DirectoryEntry class

class DiskDrive
{
  int numFiles;
  unsigned capacity;
  static int diskAccesses;
  DiskBlockInfo *disk;
public:
  DirectoryEntry *directory;
  bool *FAT;
  DiskDrive(){}
  void readFile(const char filename[]);
  int getNumFiles()const {return numFiles;}
  int getCapacity()const {return capacity;}
  int getDiskAccesses() const {return diskAccesses; }
  DiskBlock* readDiskBlock(int diskBlockID)
    { diskAccesses++ ; return new DiskBlock(disk[diskBlockID]); }
  void writeDiskBlock(DiskBlock *diskBlock, int diskBlockID)
  {
    disk[diskBlockID] = diskBlock->blockInfo;
    diskAccesses++;
  }  // copies diskBlockInfo
  void check();    
} ;  // DiskDrive class


#endif
