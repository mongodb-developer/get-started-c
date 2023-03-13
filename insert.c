// insert.c
#include "URI.h"
#include <mongoc/mongoc.h>

int main(int argc, char const *argv[]) {
  // your MongoDB URI connection string
  const char *uri_string = MY_MONGODB_URI;
  // MongoDB URI created from above string
  mongoc_uri_t *uri;
  // MongoDB Client, used to connect to the DB
  mongoc_client_t *client;

  // Error management
  bson_error_t error;

  mongoc_collection_t *collection;
  char **collection_names;
  unsigned i;

  // Object id and BSON doc
  bson_oid_t oid;
  bson_t *doc;

  char *str;

  /*
   * Required to initialize libmongoc's internals
   */
  mongoc_init();

  /*
   * Safely create a MongoDB URI object from the given string
   */
  uri = mongoc_uri_new_with_error(uri_string, &error);
  if (!uri) {
    fprintf(stderr,
            "failed to parse URI: %s\n"
            "error message:       %s\n",
            uri_string, error.message);
    return EXIT_FAILURE;
  }

  /*
   * Create a new client instance, here we use the uri we just built
   */
  client = mongoc_client_new_from_uri(uri);
  if (!client) {
    return EXIT_FAILURE;
  }

  /*
   * Register the application name so we can track it in the profile logs
   * on the server. This can also be done from the URI (see other examples).
   */
  mongoc_client_set_appname(client, "connect-example");

  /*
   * Get a handle on the database "db_name" and collection "coll_name"
   */
  collection = mongoc_client_get_collection(client, "sample_mflix", "movies");

  doc = bson_new();
  bson_oid_init(&oid, NULL);
  BSON_APPEND_OID(doc, "_id", &oid);
  BSON_APPEND_UTF8(doc, "name", "My super new picture");

  if (!mongoc_collection_insert_one(collection, doc, NULL, NULL, &error)) {
    fprintf(stderr, "%s\n", error.message);
  } else {
    printf("Document inserted!");
    /*
     * Print the document as a JSON string.
     */
    str = bson_as_canonical_extended_json(doc, NULL);
    printf("%s\n", str);
    bson_free(str);
  }

  /*
   * Release our handles and clean up libmongoc
   */

  mongoc_collection_destroy(collection);
  mongoc_uri_destroy(uri);
  mongoc_client_destroy(client);
  mongoc_cleanup();

  return EXIT_SUCCESS;
}
