/*
 * Pocris Sabin - 312CB
 */

#include "FileSystem.h"

#include <stdio.h>
#include <string.h>

#include "BinaryTree.h"

void initializeFileStructure(FileStructure *tempFS) {
  // create the root
  Folder *root = newFolder("root", NULL);

  tempFS->root = root;
  tempFS->currentFolder = root;
}

int compareFolders(void *f1, void *f2) {
  char *s1 = ((Folder *)f1)->name;
  char *s2 = ((Folder *)f2)->name;

  if (strcmp(s1, s2) == 0) return 0;

  if (strcmp(s1, s2) > 0) return 1;

  return -1;
}

int compareFiles(void *f1, void *f2) {
  char *s1 = ((File *)f1)->name;
  char *s2 = ((File *)f2)->name;

  if (strcmp(s1, s2) == 0) return 0;

  if (strcmp(s1, s2) > 0) return 1;

  return -1;
}

File *newFile(char *fileName) {
  File *tempFile = malloc(sizeof(File));
  if (!tempFile) return NULL;

  tempFile->name = malloc(strlen(fileName) + 1);
  if (!(tempFile->name)) return NULL;

  memcpy(tempFile->name, fileName, strlen(fileName) + 1);

  return tempFile;
}

Folder *newFolder(char *folderName, Folder *parent) {
  Folder *tempFolder = calloc(1, sizeof(Folder));
  if (!tempFolder) return NULL;

  tempFolder->name = malloc(strlen(folderName) + 1);
  strcpy(tempFolder->name, folderName);

  tempFolder->parentFolder = parent;
  return tempFolder;
}

void touch(FileStructure *fileStructure) {
  char *fileName = NULL;

  readStringFrom(stdin, &fileName);

  if (!fileName) return;

  Folder *tempFolder = fileStructure->currentFolder;
  Node *searchedFolder = findFolder(tempFolder->subdirectories, fileName);
  Node *seachedFile = findFile(tempFolder->files, fileName);

  if (!searchedFolder && !seachedFile) {
    File *tempFile = newFile(fileName);
    Node *tempNode = newNode(tempFile);

    addNodeToBinaryTree(&(tempFolder->files), tempNode, &compareFiles);
  } else if (searchedFolder) {
    printf("Directory %s already exists!\n", fileName);
  } else {
    printf("File %s already exists!\n", fileName);
  }

  free(fileName);
}

Node *findFile(BinaryTree binTree, char *fileName) {
  if (!binTree) return NULL;

  char *tempFileName = ((File *)binTree->data)->name;

  if (strcmp(tempFileName, fileName) == 0) return binTree;

  if (strcmp(tempFileName, fileName) > 0)
    return findFile(binTree->left, fileName);

  return findFile(binTree->right, fileName);
}

void printFileBinaryTree(BinaryTree tree) {
  if (!tree) return;

  printFileBinaryTree(tree->left);

  File *tempFile = tree->data;
  if (tempFile) printf("%s ", tempFile->name);

  printFileBinaryTree(tree->right);
}

void printFolderBinaryTree(BinaryTree tree) {
  if (!tree) return;

  printFolderBinaryTree(tree->left);

  Folder *tempFolder = tree->data;
  if (tempFolder) printf("%s ", tempFolder->name);

  printFolderBinaryTree(tree->right);
}

void ls(FileStructure *fileStructure) {
  if (!fileStructure) return;

  printFolderBinaryTree(fileStructure->currentFolder->subdirectories);
  printFileBinaryTree(fileStructure->currentFolder->files);

  printf("\n");
}

Node *findFolder(BinaryTree binTree, char *folderName) {
  if (!binTree) return NULL;

  char *tempFolderName = ((Folder *)binTree->data)->name;

  if (strcmp(tempFolderName, folderName) == 0) return binTree;

  if (strcmp(tempFolderName, folderName) > 0)
    return findFolder(binTree->left, folderName);

  return findFolder(binTree->right, folderName);
}

void makeDirectory(FileStructure *fileStructure) {
  char *folderName = NULL;

  readStringFrom(stdin, &folderName);

  if (!folderName) return;

  Folder *tempFolder = fileStructure->currentFolder;
  Node *searchedFolder = findFolder(tempFolder->subdirectories, folderName);
  Node *seachedFile = findFile(tempFolder->files, folderName);

  if (!searchedFolder && !seachedFile) {
    Folder *newDir = newFolder(folderName, fileStructure->currentFolder);
    Node *tempNode = newNode(newDir);

    addNodeToBinaryTree(&(tempFolder->subdirectories), tempNode,
                        &compareFolders);
  } else if (searchedFolder) {
    printf("Directory %s already exists!\n", folderName);
  } else {
    printf("File %s already exists!\n", folderName);
  }

  free(folderName);
}

void removeFile(FileStructure *fileStructure) {
  char *fileName = NULL;

  readStringFrom(stdin, &fileName);

  if (!fileName) return;

  Node *fileToBeRemoved =
      findFile(fileStructure->currentFolder->files, fileName);

  if (fileToBeRemoved) {
    deleteNodeToBinaryTree(&(fileStructure->currentFolder->files),
                           fileToBeRemoved);

    // dealocating memory for file
    free(((File *)fileToBeRemoved->data)->name);
    free(fileToBeRemoved->data);
    free(fileToBeRemoved);

  } else {
    printf("File %s doesn't exist!\n", fileName);
  }

  free(fileName);
}

void removeDirectory(FileStructure *fileStructure) {
  char *folderName = NULL;

  readStringFrom(stdin, &folderName);

  if (!folderName) return;

  Node *folderToBeRemoved =
      findFolder(fileStructure->currentFolder->subdirectories, folderName);

  if (folderToBeRemoved) {
    deleteNodeToBinaryTree(&(fileStructure->currentFolder->subdirectories),
                           folderToBeRemoved);
    // dealocating memory for folder
    free(((Folder *)folderToBeRemoved->data)->name);
    cleanFiles(((Folder *)folderToBeRemoved->data)->files);
    cleanFolders(((Folder *)folderToBeRemoved->data)->subdirectories);
    free(folderToBeRemoved->data);
    free(folderToBeRemoved);
  } else {
    printf("Directory %s doesn't exist!\n", folderName);
  }

  free(folderName);
}

void changeDirectory(FileStructure *fileStructure) {
  char *folderName = NULL;

  readStringFrom(stdin, &folderName);

  if (!folderName) return;

  if (strcmp("..", folderName) == 0) {
    fileStructure->currentFolder =
        fileStructure->currentFolder->parentFolder
            ? fileStructure->currentFolder->parentFolder
            : fileStructure->currentFolder;

    free(folderName);

    return;
  }

  Node *tempNode =
      findFolder(fileStructure->currentFolder->subdirectories, folderName);

  if (tempNode) {
    fileStructure->currentFolder = ((Folder *)tempNode->data);
  } else {
    printf("Directory not found!\n");
  }

  free(folderName);
}

void printWorkingDirectory(Folder *folder) {
  if (!folder) return;

  printWorkingDirectory(folder->parentFolder);

  printf("/%s", folder->name);
}

void find(FileStructure *fileStructure) {
  char *option = NULL;
  char *folderName = NULL;
  Node *tempNode = NULL;
  Folder *tempFolder = NULL;

  readStringFrom(stdin, &option);
  if (!option) return;

  readStringFrom(stdin, &folderName);
  if (!folderName) {
    free(option);
    return;
  }

  switch (option[1]) {
    case 'd':
      findFolderInFileSystem(fileStructure->root->subdirectories, folderName,
                             &tempNode);

      if (tempNode) {
        printf("Directory %s found!\n", folderName);
        printWorkingDirectory((Folder *)tempNode->data);
        printf("\n");
      } else {
        printf("Directory %s not found!\n", folderName);
      }
      break;
    case 'f':
      if (findFile(fileStructure->root->files, folderName)) {
        printf("File %s found!\n", folderName);
        printWorkingDirectory(fileStructure->root);
        printf("\n");
        break;
      }

      findFileInFileSystem(fileStructure->root->subdirectories, folderName,
                           &tempNode);
      if (tempNode) {
        printf("File %s found!\n", folderName);
        printWorkingDirectory((Folder *)tempNode->data);
        printf("\n");
      } else {
        printf("File %s not found!\n", folderName);
      }
      break;
  }

  free(option);
  free(folderName);
}

void findFolderInFileSystem(BinaryTree binTree, char *name, Node **dest) {
  if (!binTree) return;

  findFolderInFileSystem(binTree->left, name, dest);

  Folder *temp = (Folder *)binTree->data;

  if (strcmp(temp->name, name) == 0) {
    *dest = binTree;
  } else {
    findFolderInFileSystem(temp->subdirectories, name, dest);
  }

  findFolderInFileSystem(binTree->right, name, dest);
}

void findFileInFileSystem(BinaryTree binTree, char *name, Node **dest) {
  if (!binTree) return;

  findFileInFileSystem(binTree->left, name, dest);

  Folder *temp = (Folder *)binTree->data;
  Node *tempNode = findFile(temp->files, name);

  if (tempNode) {
    *dest = binTree;
  } else {
    findFileInFileSystem(temp->subdirectories, name, dest);
  }

  findFileInFileSystem(binTree->right, name, dest);
}

void cleanFiles(BinaryTree tree) {
  if (!tree) return;

  cleanFiles(tree->left);
  cleanFiles(tree->right);

  if (tree->data) {
    File *tempFile = tree->data;
    free(tempFile->name);
    free(tree->data);
    free(tree);
  }
}

void cleanFolders(BinaryTree tree) {
  if (!tree) return;

  cleanFolders(tree->left);
  cleanFolders(tree->right);

  if (tree->data) {
    Folder *tempFolder = tree->data;
    cleanFiles(tempFolder->files);
    free(tempFolder->name);

    cleanFolders(tempFolder->subdirectories);

    free(tree->data);
    free(tree);
  }
}

void cleanRoot(Folder *folder) {
  if (!folder) return;

  cleanFiles(folder->files);
  cleanFolders(folder->subdirectories);

  free(folder->name);
  free(folder);
}