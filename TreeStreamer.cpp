//#include "TreeStreamer.h"
//
//TreeStreamer::TreeStreamer(HuffmanTree* tree): treeRoot(tree), curNode(tree){}
//int* TreeStreamer::getVal(int nextBit){
//    int* val = new int;
//    if(nextBit == 0) curNode = curNode->getLeft();
//    else curNode = curNode->getRight();
//    if(curNode->haveVal()){
//        *val = curNode->getVal();
//        curNode = treeRoot;
//        return val;
//    }
//    val = 0;
//    return val;
//}
