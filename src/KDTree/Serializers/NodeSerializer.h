#ifndef NODE_SERIALIZER_H
#define NODE_SERIALIZER_H

#define NEW_NODE -1

class Node;
class FileBlocks;

class NodeSerializer {
    public:
        /**
         * @brief serializa un nodo y lo guarda en el archivo
         * @param node          nodo a serializar
         * @param nodeNumber    número del nodo (NEW_NODE si es nuevo)
         * @return nodeNumber
         * @throw FileNotSetException, FileErrorException
         */
        static unsigned serializeNode(Node* node, int nodeNumber);

        /**
         * @brief hidrata un nodo a partir de un archivo
         * @param node  número del nodo
         * @return Node en el heap
         * @throw FileNotSetException, FileErrorException
         */
        static Node* deserializeNode(unsigned node);

        /**
         * @brief asocia un nuevo archivo al serializador
         */
        static void setFile(const char* filename, unsigned _blockSize);

        /**
         * @brief asocia un nuevo archivo vacío al serializador. Borra
         * el contenido si el archivo no era nuevo.
         */
        static void newFile(const char* filename, unsigned _blockSize);
        static void freeStaticMem();
    private:
        static FileBlocks* file;
        static unsigned blockSize;

};

#endif  // NODE_SERIALIZER_H
