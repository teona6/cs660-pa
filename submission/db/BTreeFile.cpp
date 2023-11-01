#include <db/BTreeFile.h>

using namespace db;

BTreeLeafPage* BTreeFile::findLeafPage(TransactionId tid, PagesMap& dirtypages, BTreePageId* pid, Permissions perm, const Field* key) {
    while (pid->getType() == BTreePageType::INTERNAL){
        db::BTreeInternalPage* currPage = dynamic_cast<db::BTreeInternalPage*>(getPage(tid, dirtypages, pid, Permissions::READ_ONLY));
        BTreePageId* nextPid = nullptr;
        if (key == nullptr) {
            nextPid = (*currPage->begin()).getLeftChild();
        }else{
            auto it = currPage->begin();
            auto prev_it = it;

            // Find the first key greater than or equal to the given key.
            while (it != currPage->end() && key->compare(Op::GREATER_THAN, (*it).getKey())) {
                prev_it = it;
                ++it;
            }

            if (it != currPage->end()) {
                nextPid = (*it).getLeftChild();
            } else {
                nextPid = (*prev_it).getRightChild();
            }
        }
        pid = nextPid;
    }
    return dynamic_cast<BTreeLeafPage*>(getPage(tid, dirtypages, pid, perm));
}



BTreeLeafPage *BTreeFile::splitLeafPage(TransactionId tid, PagesMap &dirtypages, BTreeLeafPage *page, const Field *field) {
    // TODO pa2.3: implement
    return nullptr;
}

BTreeInternalPage *BTreeFile::splitInternalPage(TransactionId tid, PagesMap &dirtypages, BTreeInternalPage *page,
                                                Field *field) {
    // TODO pa2.3: implement
    return nullptr;
}

void BTreeFile::stealFromLeafPage(BTreeLeafPage *page, BTreeLeafPage *sibling, BTreeInternalPage *parent,
                                  BTreeEntry *entry, bool isRightSibling) {
    // TODO pa2.4: implement (BONUS)
}

void BTreeFile::stealFromLeftInternalPage(TransactionId tid, PagesMap &dirtypages, BTreeInternalPage *page,
                                          BTreeInternalPage *leftSibling, BTreeInternalPage *parent,
                                          BTreeEntry *parentEntry) {
    // TODO pa2.4: implement (BONUS)
}

void BTreeFile::stealFromRightInternalPage(TransactionId tid, PagesMap &dirtypages, BTreeInternalPage *page,
                                           BTreeInternalPage *rightSibling, BTreeInternalPage *parent,
                                           BTreeEntry *parentEntry) {
    // TODO pa2.4: implement (BONUS)
}

void BTreeFile::mergeLeafPages(TransactionId tid, PagesMap &dirtypages, BTreeLeafPage *leftPage,
                               BTreeLeafPage *rightPage, BTreeInternalPage *parent, BTreeEntry *parentEntry) {
    // TODO pa2.4: implement (BONUS)
}

void BTreeFile::mergeInternalPages(TransactionId tid, PagesMap &dirtypages, BTreeInternalPage *leftPage,
                                   BTreeInternalPage *rightPage, BTreeInternalPage *parent, BTreeEntry *parentEntry) {
    // TODO pa2.4: implement (BONUS)
}
