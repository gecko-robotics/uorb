
#include <pthread.h>
#include <unistd.h>
#include <uorb/abs_time.h>

#include "slog.h"
#include "uorb/topics/example_string.h"

void *thread_publisher() {
  struct example_string_s example_string;
  orb_publication_t *pub_example_string =
      orb_create_publication(ORB_ID(example_string));

  for (int i = 0; i < 10; i++) {
    snprintf((char *)example_string.str, EXAMPLE_STRING_STRING_LENGTH, "%d: %s",
             i, "This is a string message.");

    if (!orb_publish(pub_example_string, &example_string)) {
      LOGGER_ERROR("Publish error");
    }
    usleep(1 * 1000 * 1000);
  }

  orb_destroy_publication(&pub_example_string);
  LOGGER_WARN("Publication over.");

  return NULL;
}

int main() {
  LOGGER_INFO("uORB version: %s", orb_version());

  // One publishing thread, three subscription threads
  // pthread_t pthread_id;
  // pthread_create(&pthread_id, NULL, thread_publisher, NULL);
  // pthread_create(&pthread_id, NULL, thread_subscriber, NULL);
  // pthread_create(&pthread_id, NULL, thread_subscriber, NULL);
  // pthread_create(&pthread_id, NULL, thread_subscriber, NULL);

  // // Wait for all threads to finish
  // pthread_exit(NULL);
  thread_publisher();
}
