#ifndef POSTMANAGER_H
#define POSTMANAGER_H

#include <QList>
#include "postdata.h"

class PostManager {
public:
    static PostManager& instance();

    void addPost(const PostData &post);
    QList<PostData> getPostsByTag(const QString &tag) const;
    QList<PostData> getPostsByAuthor(const QString &author) const;
    QList<PostData> getAllPosts() const;

private:
    PostManager() = default;
    QList<PostData> posts;
};

#endif // POSTMANAGER_H