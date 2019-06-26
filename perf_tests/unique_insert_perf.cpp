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
  std::vector<char> indices = {'A', 'O', 'A', 'U', 'A', 'Z', 'I', 'i'};

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
  std::vector<char> indices = {'A', 'O', 'A', 'U', 'A', 'Z', 'I', 'i'};

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
  std::vector<char> indices = {'A', 'O', 'A', 'U', 'A', 'Z', 'I', 'i'};

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

BENCHMARK(set);
BENCHMARK(vector_binary_search_insert);
BENCHMARK(no_deduplication);
