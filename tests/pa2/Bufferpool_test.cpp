#include <gtest/gtest.h>
#include <db/Database.h>
#include <db/SkeletonFile.h>
#include <db/Utility.h>
TEST(BufferpoolTest, evictPage) {
    std::cout << "Starting evictPage Test..." << std::endl;

    db::Database::reset();
    db::BufferPool &bufferpool = db::Database::getBufferPool();
    db::Catalog &catalog = db::Database::getCatalog();
    db::SkeletonFile skeletonFile(1, db::Utility::getTupleDesc(2));
    catalog.addTable(&skeletonFile);

    db::SkeletonPageId page1(1, 0);
    db::SkeletonPageId page2(1, 1);
    db::SkeletonPageId page3(1, 2);
    bufferpool.getPage(&page1);
    std::cout << "Pages in bufferpool after getting page1: " << bufferpool.getPages().size() << std::endl;
    bufferpool.getPage(&page2);
    std::cout << "Pages in bufferpool after getting page2: " << bufferpool.getPages().size() << std::endl;
    auto page = bufferpool.getPage(&page3);
    std::cout << "Pages in bufferpool after getting page3: " << bufferpool.getPages().size() << std::endl;

    db::TransactionId tid;
    page->markDirty(tid);

    EXPECT_EQ(skeletonFile.writes, 0);
    for (int i = 0; i < 3; i++) {
        std::cout << "Attempting eviction " << i+1 << std::endl;
        EXPECT_EQ(bufferpool.getPages().size(), 3 - i);
        bufferpool.evictPage();
        std::cout << "Pages remaining after eviction " << i+1 << ": " << bufferpool.getPages().size() << std::endl;
    }

    EXPECT_EQ(bufferpool.getPages().size(), 0);
    EXPECT_EQ(skeletonFile.writes, 1);

    std::cout << "End of evictPage Test. Pages in bufferpool: " << bufferpool.getPages().size() << std::endl;
    std::cout << "Total writes to skeletonFile: " << skeletonFile.writes << std::endl;
}


TEST(BufferpoolTest, flushAllPages) {
    db::Database::reset();
    db::BufferPool &bufferpool = db::Database::getBufferPool();
    db::Catalog &catalog = db::Database::getCatalog();
    db::SkeletonFile skeletonFile(1, db::Utility::getTupleDesc(2));
    catalog.addTable(&skeletonFile);
    db::SkeletonPageId page1(1, 0);
    db::SkeletonPageId page2(1, 1);
    db::SkeletonPageId page3(1, 2);
    bufferpool.getPage(&page1);
    bufferpool.getPage(&page2);
    bufferpool.getPage(&page3);
    bufferpool.flushAllPages();
    EXPECT_EQ(bufferpool.getPages().size(), 3);
    EXPECT_EQ(skeletonFile.writes, 0);
    auto page =bufferpool.getPage(&page1);
    db::TransactionId tid;
    page->markDirty(tid);
    page = bufferpool.getPage(&page3);
    page->markDirty(tid);
    bufferpool.flushAllPages();
    EXPECT_EQ(bufferpool.getPages().size(), 3);
    EXPECT_EQ(skeletonFile.writes, 2);
}

TEST(BufferpoolTest, discardPage) {
    db::Database::reset();
    db::BufferPool &bufferpool = db::Database::getBufferPool();
    db::Catalog &catalog = db::Database::getCatalog();
    db::SkeletonFile skeletonFile(1, db::Utility::getTupleDesc(2));
    catalog.addTable(&skeletonFile);
    db::SkeletonPageId page1(1, 0);
    db::SkeletonPageId page2(1, 1);
    db::SkeletonPageId page3(1, 2);
    bufferpool.getPage(&page1);
    bufferpool.getPage(&page2);
    auto page =bufferpool.getPage(&page3);
    db::TransactionId tid;
    page->markDirty(tid);
    // initially we have 3 pages in the bufferpool and no writes to the file
    EXPECT_EQ(bufferpool.getPages().size(), 3);
    EXPECT_EQ(skeletonFile.writes, 0);
    bufferpool.discardPage(&page1);
    // we have 2 pages in the bufferpool and no writes to the file
    EXPECT_EQ(bufferpool.getPages().size(), 2);
    EXPECT_EQ(skeletonFile.writes, 0);
    bufferpool.discardPage(&page1); // nothing happens
    // we have 2 pages in the bufferpool and no writes to the file
    EXPECT_EQ(bufferpool.getPages().size(), 2);
    EXPECT_EQ(skeletonFile.writes, 0);
    bufferpool.discardPage(&page3);
    // we have 1 pages in the bufferpool and no writes to the file
    EXPECT_EQ(bufferpool.getPages().size(), 1);
    EXPECT_EQ(skeletonFile.writes, 0);
}

TEST(BufferpoolTest, flushPage) {
    db::Database::reset();
    db::BufferPool &bufferpool = db::Database::getBufferPool();
    db::Catalog &catalog = db::Database::getCatalog();
    db::SkeletonFile skeletonFile(1, db::Utility::getTupleDesc(2));
    catalog.addTable(&skeletonFile);
    db::SkeletonPageId page1(1, 0);
    db::SkeletonPageId page2(1, 1);
    db::SkeletonPageId page3(1, 2);
    bufferpool.getPage(&page1);
    bufferpool.getPage(&page2);
    auto page = bufferpool.getPage(&page3);
    db::TransactionId tid;
    page->markDirty(tid);
    // initially we have 3 pages in the bufferpool and no writes to the file
    EXPECT_EQ(bufferpool.getPages().size(), 3);
    EXPECT_EQ(skeletonFile.writes, 0);
    bufferpool.flushPage(&page1);
    // we have 3 pages in the bufferpool and no writes to the file
    EXPECT_EQ(bufferpool.getPages().size(), 3);
    EXPECT_EQ(skeletonFile.writes, 0);
    bufferpool.flushPage(&page1); // nothing happens
    // we have 3 pages in the bufferpool and no writes to the file
    EXPECT_EQ(bufferpool.getPages().size(), 3);
    EXPECT_EQ(skeletonFile.writes, 0);
    bufferpool.flushPage(&page3);
    // we have 3 pages in the bufferpool and no writes to the file
    EXPECT_EQ(bufferpool.getPages().size(), 3);
    EXPECT_EQ(skeletonFile.writes, 1);
}

TEST(BufferpoolTest, flushPages) {
    db::Database::reset();
    db::BufferPool &bufferpool = db::Database::getBufferPool();
    db::Catalog &catalog = db::Database::getCatalog();
    db::SkeletonFile skeletonFile(1, db::Utility::getTupleDesc(2));
    catalog.addTable(&skeletonFile);
    db::SkeletonPageId page1(1, 0);
    db::SkeletonPageId page2(1, 1);
    db::SkeletonPageId page3(1, 2);
    db::TransactionId tid1;
    db::TransactionId tid2;
    auto page = bufferpool.getPage(&page1);
    page->markDirty(tid1);
    page = bufferpool.getPage(&page2);
    page->markDirty(tid2);
    page = bufferpool.getPage(&page3);
    page->markDirty(tid1);

    // initially we have 3 pages in the bufferpool and no writes to the file
    EXPECT_EQ(bufferpool.getPages().size(), 3);
    EXPECT_EQ(skeletonFile.writes, 0);
    bufferpool.flushPages(tid1);
    EXPECT_EQ(bufferpool.getPages().size(), 3);
    EXPECT_EQ(skeletonFile.writes, 2);
    bufferpool.flushPages(tid1);
    EXPECT_EQ(bufferpool.getPages().size(), 3);
    EXPECT_EQ(skeletonFile.writes, 2);
}
