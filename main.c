/*
 * Pocris Sabin - 312CB
 */

#include <stdio.h>
#include <string.h>

#include "BinaryTree.h"
#include "FileSystem.h"
#include "IO.h"

int main() {
  // the object we use to represent the file system
  FileStructure fileStructure;

  initializeFileStructure(&fileStructure);

  for (;;) {
    switch (getCommand(stdin)) {
      case TOUCH:
        touch(&fileStructure);
        break;

      case MKDIR:
        makeDirectory(&fileStructure);
        break;

      case LS:
        ls(&fileStructure);
        break;

      case RM:
        removeFile(&fileStructure);
        break;

      case RMDIR:
        removeDirectory(&fileStructure);
        break;

      case CD:
        changeDirectory(&fileStructure);
        break;

      case PWD:
        printWorkingDirectory(fileStructure.currentFolder);
        printf("\n");
        break;

      case FIND:
        find(&fileStructure);
        break;

      default:
        cleanRoot(fileStructure.root);
        return 0;
    }
  }
}