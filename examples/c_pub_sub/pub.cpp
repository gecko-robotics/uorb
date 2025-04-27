#include <uorb/uorb.h>
// #include <uORB/topics/pasta_information.h>
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
    int i = 0;
    struct example_string_s data = {};
    orb_advert_t handle = orb_advertise(ORB_ID(data), &data);
    if (handle == nullptr) {
        return -1;
    }
    while (true) {
        // data.timestamp = hrt_absolute_time();
        // data.customer_table_id = 42;
        // data.menu_name = 1; // PASTA_MENU_CARBONARA
        // data.cooked_texture = 2; // PASTA_TEXTURE_AL_DENTE

        snprintf((char *)data.str, EXAMPLE_STRING_STRING_LENGTH, "%d: %s",
        i++, "This is a string message.");

        orb_publish(ORB_ID(data), handle, &data);
        sleep(1); // Publish every second
    }
    return 0;
}