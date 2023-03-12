/*
 * Pocris Sabin - 312CB
 */

#ifndef _FILE_SYS_
#define _FILE_SYS_

// headers
#include <string.h>

#include "BinaryTree.h"
#include "IO.h"

// Types

typedef struct folder {
  char *name;
  BinaryTree files;
  BinaryTree subdirectories;
  struct folder *parentFolder;
} Folder;

typedef struct file {
  char *name;
} File;

typedef struct fileStructure {
  Folder *root;
  Folder *currentFolder;
} FileStructure;

// Functions

// initializing the fs with an empty 'root' folder
void initializeFileStructure(FileStructure *tempFS);

// creates and returns a new file with the given name
File *newFile(char *fileName);

// creates and returns a new folder with the given name
Folder *newFolder(char *folderName, Folder *parent);

// functions used for comparing the elements in the binary tree
int compareFolders(void *f1, void *f2);
int compareFiles(void *f1, void *f2);

// given a binary tree, it searches for a file in that tree
// if it finds it, it returns the node with the file
Node *findFile(BinaryTree binTree, char *fileName);

// given a binary tree, it searches for a folder in that tree
// if it finds it, it returns the node with the folder
Node *findFolder(BinaryTree binTree, char *folderName);

// it searches for a file/folder starting from the root
// if it is found, it prints it's pwd
void find(FileStructure *fileStructure);

// saves in `dest` the address of the node representing the file searched
// it goes through all folders and their subfolders from the given tree
void findFolderInFileSystem(BinaryTree binTree, char *name, Node **dest);

// saves in `dest` the address of the node representing the folder searched
// it goes through all folders and their subfolders from the given tree
void findFileInFileSystem(BinaryTree binTree, char *name, Node **dest);

// print the working directory of a folder by going recursively to it's parents
void printWorkingDirectory(Folder *folder);

// removes a file from the workind directory
void removeFile(FileStructure *fileStructure);
// removes a folder from the workind directory
void removeDirectory(FileStructure *fileStructure);

// changes the current folder of the file structure
void changeDirectory(FileStructure *fileStructure);

// creates a new file in the file structure
void touch(FileStructure *fileStructure);

// creates a new folder in the file structure
void makeDirectory(FileStructure *fileStructure);

// list the files and folders from the working directory
void ls(FileStructure *fileStructure);

void printFileBinaryTree(BinaryTree tree);
void printFolderBinaryTree(BinaryTree tree);

// dealocates the memory used by the a folder's subdirectories
// and their content
void cleanFolders(BinaryTree tree);

// dealocates the memory used by the files from a directory
void cleanFiles(BinaryTree tree);

// dealocates the memory used by the root it's content
void cleanRoot(Folder *folder);

#endif