#include "postmanager.h"

PostManager& PostManager::instance()
{
    static PostManager manager;
    return manager;
}

void PostManager::addPost(const PostData &post)
{
    posts.append(post);
}

QList<PostData> PostManager::getPostsByTag(const QString &tag) const
{
    QList<PostData> result;
    for (const PostData &post : posts) {
        if (post.tag == tag) {
            result.append(post);
        }
    }
    return result;
}

QList<PostData> PostManager::getAllPosts() const
{
    return posts;
}

QList<PostData> PostManager::getPostsByAuthor(const QString &author) const
{
    QList<PostData> result;
    for (const PostData &post : posts) {
        if (post.author == author) {
            result.append(post);
        }
    }
    return result;
}