#include "NodeSerializer.h"
#include "../InnerNode.h"
#include "../LeafNode.h"
#include "../../File/FileBlocks.h"
#include "../../Exceptions/FileNotSetException.h"
#include "../../Exceptions/FileErrorException.h"

#ifndef BLOCKSIZE
#define BLOCKSIZE 4096
#endif

FileBlocks* NodeSerializer::file = NULL;
unsigned NodeSerializer::blockSize = BLOCKSIZE;

unsigned NodeSerializer::serializeNode(Node* node, int nodeNumber) {
    if (!file)
        throw FileNotSetException();

    char* buffer = new char[blockSize];
    int bytes = node->serialize(buffer);

    unsigned blockNumber;
    if (nodeNumber == NEW_NODE) {
        blockNumber = file->getFreeBlock();
        if (!file->insert(buffer, blockNumber))
            throw FileErrorException();
    }
    else {
        blockNumber = nodeNumber;
        if (!file->update(buffer, blockNumber))
            throw FileErrorException();
    }

    delete[] buffer;
    return blockNumber;
}

Node* NodeSerializer::deserializeNode(unsigned node) {
    if (!file)
        throw FileNotSetException();

    Node* newNode;
    char* buffer = (char*)file->find(&node);
    if (!buffer)
        throw FileErrorException();

    if (buffer[0] & IS_LEAF)
        newNode = new LeafNode();
    else
        newNode = new InnerNode();

    int bytes = newNode->deserialize(buffer);

    delete[] buffer;
    return newNode;
}

void NodeSerializer::setFile(const char* filename, unsigned _blockSize) {
    delete file;
    file = new FileBlocks(filename, _blockSize);
    blockSize = _blockSize;
}

void NodeSerializer::newFile(const char* filename, unsigned _blockSize) {
    setFile(filename, _blockSize);
    file->deleteData();
}

void NodeSerializer::freeStaticMem() {
    delete file;
    file = NULL;
}
