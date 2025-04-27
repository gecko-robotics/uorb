
#include <pthread.h>
#include <unistd.h>
#include <uorb/abs_time.h>

#include "slog.h"
#include "uorb/topics/example_string.h"


void *thread_subscriber() {
  orb_subscription_t *sub_example_string =
      orb_create_subscription(ORB_ID(example_string));

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
#endif

  struct orb_pollfd pollfds[] = {{.fd = sub_example_string, .events = POLLIN}};
  int timeout = 2000;

  while (true) {
    if (0 < orb_poll(pollfds, ARRAY_SIZE(pollfds), timeout)) {
      struct example_string_s example_string;
      orb_copy(sub_example_string, &example_string);
      LOGGER_INFO("Receive msg: \"%s\"", example_string.str);
    } else {
      LOGGER_WARN("Got no data within %d milliseconds", timeout);
      break;
    }
  }

  orb_destroy_subscription(&sub_example_string);

  LOGGER_WARN("subscription over");
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
  thread_subscriber();
}
