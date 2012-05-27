#include "Node.h"
#include "Record.h"

#define IS_LEAF 0x80

class LeafNode: public Node{
    public:
        LeafNode();
        LeafNode(unsigned _level);

        int insert(Record* record);
        Node* split();

    //	virtual Node* nextLeaf();

        int serialize(char* buffer);
        int deserialize(const char* buffer);

        ~LeafNode();

        /** fea idea, pero es por falta de tiempo */
#ifdef TESTING
        friend class SerializersTest;
#endif
    private:
        std::vector<Record* > elements;
};
