#include <algorithm>
#include <cstddef>
#include <fmt/core.h>
#include <functional>
#include <iostream>
#include <optional>
#include <queue>
#include <vector>
#include <ranges>
#include <random>

#include <CLI/CLI.hpp>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

// This file will be generated automatically when you run the CMake configuration step.
// It creates a namespace called `myproject`.
// You can modify the source template at `configured_files/config.hpp.in`.
#include <internal_use_only/config.hpp>

using json = nlohmann::json;

struct Limit
{
  size_t low;
  size_t high;
};

size_t partition(std::vector<int> &arr, Limit limit)
{
  const int pivot = arr[limit.high];
  size_t index = limit.low - 1;

  for (size_t i = limit.low; i < limit.high; ++i) {
    if (arr[i] <= pivot) {
        index++;
        const int tmp = arr[i];
        arr[i] = arr[index];
        arr[index] = tmp;
      }
    }
  index++;

  arr[limit.high] = arr[index];
  arr[index] = pivot;
  return index;
}

void quicksort(std::vector<int> &arr, Limit limit)// NOLINT(misc-no-recursion,-warnings-as-errors)
{
  if (limit.low >= limit.high) { return; }

  const size_t pivotIndex = partition(arr, limit);
  quicksort(arr, Limit {limit.low, pivotIndex - 1});
  quicksort(arr, Limit {pivotIndex + 1, limit.high});
}


// NOLINTNEXTLINE(bugprone-exception-escape)
int main(int argc, const char **argv)
{
  try {
    CLI::App app{ fmt::format("{} version {}", myproject::cmake::project_name, myproject::cmake::project_version) };

    std::optional<std::string> message;
    app.add_option("-m,--message", message, "A message to print back out");
    bool show_version = false;
    app.add_flag("--version", show_version, "Show version information");
    const int QUEUE_SIZE_DEFAULT = 100;
    std::optional<int> queue_size = QUEUE_SIZE_DEFAULT;
    app.add_option("-n,--number", queue_size, "Number of int to store in a queue");

    CLI11_PARSE(app, argc, argv);

    if (show_version) {
      fmt::print("{}\n", myproject::cmake::project_version);
      return EXIT_SUCCESS;
    }

    // Use the default logger (stdout, multi-threaded, colored)
    spdlog::info("Hello, {}!", "World");

    if (message) {
      fmt::print("Message: '{}'\n", *message);
    } else {
      fmt::print("No Message Provided :(\n");
    }


    // First create an instance of an engine.
    std::random_device rnd_device;
    // Specify the engine and distribution.
    std::mt19937 mersenne_engine{ rnd_device() };// Generates random integers
    const int MIN = 1;
    const int MAX = *queue_size;
    std::uniform_int_distribution<int> dist{ MIN, MAX };

    auto gen = [&dist, &mersenne_engine]() { return dist(mersenne_engine); };

    // const size_t MAX_VECTOR_SIZE = 10;
    std::vector<int> vec(static_cast<size_t>(*queue_size));
    std::generate(std::begin(vec), std::end(vec), gen);

    std::sort(vec.begin(), vec.end());

    // quicksort(vec, Limit {0, vec.size() - 1});
    for (const int& num : vec) {
      fmt::print("{} ", num);
    }
    fmt::print("\n");


    std::deque<int> the_queue = {};
    const int default_queue_size = 10;
    int queue_size_n = default_queue_size;
    if (queue_size) { queue_size_n = *queue_size; }
    for (auto i = 0; i < queue_size_n; ++i) {
      if (i % 2 == 0) {
        the_queue.push_back(i);
      } else {
        the_queue.push_front(i);
      }
    }

    json list = json::array();

    // for (const auto &num : the_queue) { fmt::print("number: '{}'\n", num); }

  } catch (const std::exception &e) {
    spdlog::error("Unhandled exception in main: {}", e.what());
  }
}
