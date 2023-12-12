// list_collections.c
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

  mongoc_database_t *database;
  mongoc_collection_t *collection;
  char **collection_names;
  unsigned i;

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
  database = mongoc_client_get_database(client, "sample_mflix");

  // getting all collection names, here we're not passing in any options
  if ((collection_names = mongoc_database_get_collection_names_with_opts(
           database, NULL, &error))) {
    for (i = 0; collection_names[i]; i++) {
      printf("%s\n", collection_names[i]);
    }
    bson_strfreev (collection_names);
  } else {
    fprintf(stderr, "Error: %s\n", error.message);
    return EXIT_FAILURE;
  }

  /*
   * Release our handles and clean up libmongoc
   */

  mongoc_database_destroy(database);
  mongoc_uri_destroy(uri);
  mongoc_client_destroy(client);
  mongoc_cleanup();

  return EXIT_SUCCESS;
}
