#include <benchmark/benchmark.h>

void bs_insert(const std::string& item, std::vector<std::string>& vec)
{
  auto it = std::lower_bound(vec.begin(), vec.end(), item );
  if(it== vec.end() || *it != item)
  {
    vec.insert(it, item);
  }
}

static void set(benchmark::State& state) {
  std::vector<std::string> inter = {"UA", "UOA", {(char)128}};
  unsigned char ns = 140;
  std::vector<char> indices = {'A', 'O', 'A', 'U', 'A', 'Z', 'I', 'i', 'b', 'A', 'c', 'U', 'Z'};

  for (auto _ : state)
  {
    std::vector<std::string> res;

    std::set<std::string> new_interactions;
    for(auto interaction : inter)
    {
      interaction.push_back((char)ns);
      new_interactions.insert(interaction);
    }

    for (auto& c : indices)
    {
      new_interactions.insert({(char)c, (char)ns});
    }

      res.insert(res.end(), new_interactions.begin(), new_interactions.end());
  }
}

static void no_deduplication(benchmark::State& state) {
  std::vector<std::string> inter = {"UA", "UOA", {(char)128}};
  unsigned char ns = 140;
  std::vector<char> indices = {'A', 'O', 'A', 'U', 'A', 'Z', 'I', 'i', 'b', 'A', 'c', 'U', 'Z'};

  for (auto _ : state)
  {
    std::vector<std::string> res;

    for(auto interaction : inter)
    {
      interaction.push_back((char)ns);
      res.push_back(interaction);
    }

    for (auto& c : indices)
    {
      res.emplace_back((char)c, (char)ns);
    }
  }
}

static void vector_binary_search_insert(benchmark::State& state) {
   std::vector<std::string> inter = {"UA", "UOA", {(char)128}};
  unsigned char ns = 140;
  std::vector<char> indices = {'A', 'O', 'A', 'U', 'A', 'Z', 'I', 'i', 'b', 'A', 'c', 'U', 'Z'};

  for (auto _ : state)
  {
    std::vector<std::string> res;

    for(auto interaction : inter)
    {
      interaction.push_back((char)ns);
      bs_insert(interaction, res);
    }

    for (auto& c : indices)
    {
      bs_insert({(char)c, (char)ns}, res);
    }
  }
}

constexpr unsigned char printable_start = ' ';
constexpr unsigned char printable_end = '~';
constexpr unsigned char printable_ns_size = printable_end - printable_start;

static void fixed_bool_bookkeeping(benchmark::State& state) {
   std::vector<std::string> inter = {"UA", "UOA", {(char)128}};
  unsigned char ns = 140;
  std::vector<char> indices = {'A', 'O', 'A', 'U', 'A', 'Z', 'I', 'i', 'b', 'A', 'c', 'U', 'Z'};

  for (auto _ : state)
  {
    static thread_local std::array<bool, printable_ns_size> found_namespaces;
    found_namespaces.fill(false);
    std::vector<std::string> res;

    for(auto interaction : inter)
    {
      interaction.push_back((char)ns);
      res.push_back(interaction);
    }

    for (auto& c : indices)
    {
      if (c >= printable_start && c <=  printable_end &&
          !found_namespaces[c - printable_start])
      {
        found_namespaces[c - printable_start] = true;
        res.push_back({(char)c, (char)ns});
      }
    }
  }
}

BENCHMARK(set);
BENCHMARK(vector_binary_search_insert);
BENCHMARK(no_deduplication);
BENCHMARK(fixed_bool_bookkeeping);
