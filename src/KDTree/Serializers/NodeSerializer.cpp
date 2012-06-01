#include "NodeSerializer.h"
#include "../Node/InnerNode.h"
#include "../Node/LeafNode.h"
#include "../../File/FileBlocks.h"
#include "../../Exceptions/FileNotSetException.h"
#include "../../Exceptions/FileErrorException.h"

#ifndef BLOCKSIZE
#define BLOCKSIZE 4096
#endif

FileBlocks* NodeSerializer::file = NULL;
unsigned NodeSerializer::blockSize = BLOCKSIZE;

unsigned NodeSerializer::serializeNode(Node* node) {

	return serializeNode(node, NEW_NODE);
}


unsigned NodeSerializer::serializeNode(Node* node, int nodeNumber) {
    if (!file)
        throw FileNotSetException();

    char* buffer = new char[blockSize];
    int bytes = node->serialize(buffer);

    unsigned blockNumber;
    if (nodeNumber == NEW_NODE) {
        blockNumber = file->getFreeBlock();
        if (!file->insert(buffer, blockNumber, bytes))
            throw FileErrorException();
    }
    else {
        blockNumber = nodeNumber;
        if (!file->update(buffer, blockNumber, bytes))
            throw FileErrorException();
    }

    delete[] buffer;
    return blockNumber;
}

Node* NodeSerializer::deserializeNode(unsigned node) {

std::cout<< "deserializeNode" <<std::endl;

	if (!file)
        throw FileNotSetException();

std::cout<< "NewNODE" <<std::endl;

	Node* newNode= NULL;

std::cout<< "FILE FIND" <<std::endl;

    char* buffer = (char*)file->find(& node);

std::cout<< "BUFFER" <<std::endl;


    if (!buffer){

std::cout << " !BUFFER => FILE ERROR" << std::endl;

    	throw FileErrorException();
    }
    if (buffer[0] & IS_LEAF){
std::cout<< "New LEAF" <<std::endl;

        newNode = new LeafNode();
    }
    else{
std::cout<< "New INNER" <<std::endl;

        newNode = new InnerNode();
    }

std::cout<< "DESERIALIZE BUFFER" <<std::endl;

    int bytes = newNode->deserialize(buffer);

    delete[] buffer;
    return newNode;
}

void NodeSerializer::setFile(const char* filename, unsigned _blockSize) {
    delete file;
    file = new FileBlocks(filename, _blockSize);
    blockSize = _blockSize;
}

void NodeSerializer::setFile(FileBlocks* treeFile) {
    delete file;
    file = treeFile;
    blockSize = treeFile->getBlockSize();
}

void NodeSerializer::newFile(const char* filename, unsigned _blockSize) {
    setFile(filename, _blockSize);
    file->deleteData();
}

void NodeSerializer::freeStaticMem() {
    delete file;
    file = NULL;
}
