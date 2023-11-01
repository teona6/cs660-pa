#include <db/BufferPool.h>
#include <db/Database.h>
#include <iostream>

using namespace db;

void BufferPool::evictPage() {
    // If the pages map is empty, there's nothing to evict
    if (pages.empty()) {
        return;
    }

    // Get the iterator to the first page in the map
    auto it = pages.begin();

    // If the page is dirty, write it to disk
    if (it->second->isDirty().has_value()) {
        flushPage(it->first);
    }

    // Remove the page from the map and deallocate memory
    delete it->second;
    pages.erase(it);
}


void BufferPool::flushAllPages() {
    // Iterate over all pages in the buffer pool
    for (auto &entry : pages) {
        const PageId *pid = entry.first;
        flushPage(pid);
    }
}

void BufferPool::discardPage(const PageId *pid) {
    // Find the page in the buffer pool
    auto it = pages.find(pid);
    
    // If the page is found, erase it from the buffer pool
    if (it != pages.end()) {
        pages.erase(it);
    }
}

void BufferPool::flushPage(const PageId *pid) {
    // Check if the page exists in the buffer pool
    auto it = pages.find(pid);
    if (it == pages.end()) {
        return;
    }

    Page *page = it->second;
    // we only write dirty pages
    if (!page->isDirty()) {
        return;
    }

    // Use the Catalog to retrieve the SkeletonFile for the page's table ID
    Catalog &catalog = Database::getCatalog();
    SkeletonFile *skeletonFile = dynamic_cast<SkeletonFile *>(catalog.getDatabaseFile(pid->getTableId()));

    skeletonFile->writePage(page);

    // Mark the page as no longer dirty
    page->markDirty(std::nullopt);
}

void BufferPool::flushPages(const TransactionId &tid) {
    // Iterate over all pages in the buffer pool
    for (auto &entry : pages) {
        Page *page = entry.second;

        // Check if the page's transaction ID matches the given tid and if the page is dirty
        if (page->isDirty() == tid) {
            flushPage(entry.first);
        }
    }
}


void db::BufferPool::insertTuple(const TransactionId &tid, int tableId, Tuple *t) {

}

void db::BufferPool::deleteTuple(const TransactionId &tid, Tuple *t) {

}
