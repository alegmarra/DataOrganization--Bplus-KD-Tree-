
#include<vector>


class KDtree;
class Node;
class FileAbstract;

class KDtreeSerializer{

public:
	static  FileAbstract* serialize(KDtree* object);

	static  Node* deSerialize(FileAbstract* onFile);

	static void setFreeNode(unsigned nodeNumber, FileAbstract* treeFile);

	static std::vector<unsigned> getFreeNodes(FileAbstract* treeFile);

};
