// filesys.h 
//	Data structures to represent the Nachos file system.
//
//	A file system is a set of files stored on disk, organized
//	into directories.  Operations on the file system have to
//	do with "naming" -- creating, opening, and deleting files,
//	given a textual file name.  Operations on an individual
//	"open" file (read, write, close) are to be found in the OpenFile
//	class (openfile.h).
//
//	We define two separate implementations of the file system. 
//	The "STUB" version just re-defines the Nachos file system 
//	operations as operations on the native UNIX file system on the machine
//	running the Nachos simulation.
//
//	The other version is a "real" file system, built on top of 
//	a disk simulator.  The disk is simulated using the native UNIX 
//	file system (in a file named "DISK"). 
//
//	In the "real" implementation, there are two key data structures used 
//	in the file system.  There is a single "root" directory, listing
//	all of the files in the file system; unlike UNIX, the baseline
//	system does not provide a hierarchical directory structure.  
//	In addition, there is a bitmap for allocating
//	disk sectors.  Both the root directory and the bitmap are themselves
//	stored as files in the Nachos file system -- this causes an interesting
//	bootstrap problem when the simulated disk is initialized. 
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#ifndef FS_H
#define FS_H
#define MAX_OPEN_FILE 10
//#define FILESYS_STUB // =DDDDDDDDDDDDDDDDDDDDDDD
typedef int OpenFileId;	

#include "copyright.h"
#include "sysdep.h"
#include "openfile.h"

#ifdef FILESYS_STUB 		// Temporarily implement file system calls as 
				// calls to UNIX, until the real file system
				// implementation is available
class FileSystem {
  public:
	OpenFile **openFile;
    FileSystem() {
		openFile = new OpenFile*[MAX_OPEN_FILE];
		for (int i = 0; i < MAX_OPEN_FILE; i++) 
			openFile[i] = NULL;
	}
	~FileSystem() {
		for (int i = 0; i < MAX_OPEN_FILE; i++) 
			if (openFile[i])
				delete openFile[i];
		delete[] openFile;
	}
	OpenFile *Open(char *name) {
		int fileDescriptor = OpenForReadWrite(name, FALSE);
		if (fileDescriptor == -1) 
			return NULL;
		return new OpenFile(fileDescriptor, name);
	}
	
    bool Create(char *name) {
		int fileDescriptor = OpenForWrite(name);

		if (fileDescriptor == -1) return FALSE;
		Close(fileDescriptor); 
		return TRUE; 
	}

    OpenFileId OpenWithId(char *name) {
		OpenFileId openFileId;
		for (int i = 0; i < MAX_OPEN_FILE; i++) 
			if (openFile[i] == NULL)
			{
				openFileId = i;
				break;
			}
		int fileDescriptor = OpenForReadWrite(name, FALSE);

		if (fileDescriptor == -1) 
			return -1;
		openFile[openFileId] = new OpenFile(fileDescriptor, name);
		return openFileId;
    }

	bool Close(OpenFileId openFileId) {
		if (openFileId < 0 || openFileId >= MAX_OPEN_FILE)
			return false;
		if (openFile[openFileId] == NULL)
			return false;
		else
		{
			delete openFile[openFileId];
			openFile[openFileId] = NULL;
			return true;
		}
	}
	int Read(char* buffer, int size, int openFileId){
		if (openFileId < 0 || openFileId >= MAX_OPEN_FILE) 
			return -1;
		if (openFile[openFileId] == NULL) 
			return -1;
		int result = openFile[openFileId]->Read(buffer,size);
		cout << result <<endl;
		if (result != size) 
			return -1;
		return result;
	}
	int Write(char *buffer, int size, int openFileId) {
		if (openFileId < 0 || openFileId >  MAX_OPEN_FILE) 
			return -1;
		if (openFile[openFileId] == NULL )
			return -1;
		return openFile[openFileId]->Write(buffer, size);
    }
	int Seek(int pos, int openFileId) {
        if (openFileId < 0 || openFileId >  MAX_OPEN_FILE) 
			return -1;
        if (openFile[openFileId] == NULL) 
			return -1;
        if (pos == -1) 
			pos = openFile[openFileId]->Length();
        if (pos < 0 || pos > openFile[openFileId]->Length()) 
			return -1;
        return openFile[openFileId]->Seek(pos);
    }

    bool Remove(char *name) { 
		for (int i = 0; i < MAX_OPEN_FILE; i++) {
			if (openFile[i] && strcmp(name, openFile[i]->getFilename()) == 0)
				return false;
		}
		return Unlink(name) == 0; 
	}

};

#else // FILESYS
class FileSystem {
  public:
    FileSystem(bool format);		// Initialize the file system.
					// Must be called *after* "synchDisk" 
					// has been initialized.
    					// If "format", there is nothing on
					// the disk, so initialize the directory
    					// and the bitmap of free blocks.

    bool Create(char *name, int initialSize);  	
					// Create a file (UNIX creat)

    OpenFile* Open(char *name); 	// Open a file (UNIX open)

    bool Remove(char *name);  		// Delete a file (UNIX unlink)

    void List();			// List all the files in the file system

    void Print();			// List all the files and their contents

  private:
   OpenFile* freeMapFile;		// Bit map of free disk blocks,
					// represented as a file
   OpenFile* directoryFile;		// "Root" directory -- list of 
					// file names, represented as a file
};

#endif // FILESYS

#endif // FS_H
