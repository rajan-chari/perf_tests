#include "v_hashmap.h"
#include "hash.h"
#include "parse_primitives.h"
#include "memory.h"
#include "sparsehash/dense_hash_map"
#include <unordered_map>
#include <string>
#include <vector>
#include <benchmark/benchmark.h>

const std::vector<std::string> inputs = {
    "abc",
    "def",
    "abcdef",
    "this is a string",
    "another string",
    "what has my life become?",
    "supercalifragilisticexpialidocious",
    "WHHAAAAAARGHARBL",
    "HASHING ALL THE MAPS!",
    "something boring",
    "words, words, words",
    "another 300 words now",
    "quality",
    "remember",
    "hospitality",
    "rack",
    "sentence",
    "unlawful",
    "budget",
    "rabbit",
    "patient",
    "chocolate",
    "conversation",
    "television",
    "owl",
    "able",
    "part",
    "alcohol",
    "activate",
    "short",
    "excavate",
    "park",
    "state",
    "delete",
    "sting",
    "distortion",
    "system",
    "direct",
    "initial",
    "miracle",
    "suitcase",
    "movie",
    "invite",
    "night",
    "position",
    "experienced",
    "triangle",
    "ball",
    "sailor",
    "tribe",
    "congress",
    "unfortunate",
    "productive",
    "poem",
    "appear",
    "thin",
    "comment",
    "conviction",
    "letter",
    "chorus",
    "panel",
    "teenager",
    "distributor",
    "mark",
    "grandmother",
    "scenario",
    "healthy",
    "outline",
    "general",
    "ego",
    "pilot",
    "margin",
    "source",
    "characteristic",
    "haircut",
    "win",
    "gasp",
    "break down",
    "essay",
    "notebook",
    "raid",
    "supply",
    "consumer",
    "money",
    "funeral",
    "torch",
    "hostile",
    "ward",
    "pile",
    "butterfly",
    "movement",
    "spread",
    "safety",
    "hypnothize",
    "dominant",
    "stitch",
    "game",
    "brink",
    "consider",
    "repetition",
    "resign",
    "carriage",
    "visible",
    "breeze",
    "extreme",
    "custody",
    "factory",
    "coma",
    "still",
    "loan",
    "remedy",
    "twilight",
    "calculation",
    "concession",
    "conscience",
    "material",
    "bucket",
    "strap",
    "unfair",
    "staff",
    "career",
    "attitude",
    "executrix",
    "wound",
    "vegetable",
    "intermediate",
    "kick",
    "faint",
    "origin",
    "incentive",
    "gravel",
    "hide",
    "offense",
    "crossing",
    "compound",
    "track",
    "bark",
    "sausage",
    "garage",
    "debut",
    "hesitate",
    "stem",
    "fork",
    "root",
    "mourning",
    "stir",
    "president",
    "snap",
    "profile",
    "escape",
    "feed",
    "construct",
    "damage",
    "navy",
    "will",
    "generate",
    "loyalty",
    "scream",
    "alarm",
    "glory",
    "mountain",
    "full",
    "creation",
    "stand",
    "stall",
    "helicopter",
    "suspect",
    "thirsty",
    "fuss",
    "reason",
    "kidnap",
    "privacy",
    "thesis",
    "divorce",
    "interactive",
    "pony",
    "brown",
    "lost",
    "abuse",
    "manner",
    "rent",
    "request",
    "initiative",
    "chord",
    "dome",
    "bad",
    "upset",
    "sale",
    "magnetic",
    "throw",
    "short circuit",
    "ideal",
    "toss",
    "leave",
    "award",
    "term",
    "student",
    "drawing",
    "inspiration",
    "video",
    "breed",
    "national",
    "contempt",
    "deputy",
    "drink",
    "blow",
    "train",
    "set",
    "carve",
    "west",
    "summit",
    "help",
    "society",
    "beard",
    "engineer",
    "rich",
    "stake",
    "glare",
    "bundle",
    "challenge",
    "sport",
    "sweater",
    "financial",
    "slot",
    "hunting",
    "wait",
    "bee",
    "folk",
    "potential",
    "tactic",
    "reward",
    "vegetation",
    "liberal",
    "exotic",
    "horoscope",
    "ice cream",
    "plot",
    "crack",
    "kettle",
    "urine",
    "address",
    "verdict",
    "offspring",
    "trade",
    "smoke",
    "slippery",
    "bring",
    "chauvinist",
    "symbol",
    "journal",
    "increase",
    "overall",
    "core",
    "plain",
    "cabinet",
    "gutter",
    "sip",
    "autonomy",
    "banish",
    "peace",
    "river",
    "formal",
    "rhetoric",
    "adult",
    "shadow",
    "resource",
    "bar",
    "graduate",
    "capture",
    "critical",
    "effect",
    "reactor",
    "raise",
    "transfer",
    "housewife",
    "deal",
    "excitement",
    "speech",
    "reluctance",
    "deter",
    "oral",
    "stick",
    "wake",
    "recycle",
    "protest",
    "output",
    "embrace",
    "flight",
    "kit",
    "shaft",
    "trap",
    "vision",
    "ban",
    "flag",
    "priority",
    "aid",
    "stomach",
    "foot",
    "give",
    "motorcycle",
    "round",
    "medieval",
    "administration",
    "neighbour",
    "break in",
    "nap",
    "moving",
    "bitch",
    "cereal",
    "permission",
    "spy",
    "station"
};

using v_map = v_hashmap<substring, int>;
using v_map_string = v_hashmap<std::string, int>;
using g_densemap = google::dense_hash_map<std::string, int>;
using std_hashmap = std::unordered_map<std::string, int>;

static const size_t SMALL_SIZE = 10;

inline void add_map_entry_vhashmap_no_replace(v_map& map, const std::string & key, int value)
{
    char * begin = (char*)key.c_str();
    size_t len = key.length();
    uint64_t hash = uniform_hash(key.c_str(), len, 378401);
    substring search_key = {(char*)key.c_str(), (char*)key.c_str() + len};
    
    if(map.contains(search_key, hash))
    {
        // key already exists. skip
        return;
    }
    
    char * newmem = calloc_or_throw<char>(len);
    memcpy(newmem, begin, len);
    substring insert_key = {newmem, newmem + len};
    map.put(insert_key, hash, value);
}
inline void add_map_entry_vhashmap_no_replace(v_map_string& map, const std::string & key, int value)
{
    uint64_t hash = uniform_hash(key.c_str(), key.length(), 378401);
    
    if(map.contains(key, hash))
    {
        // key already exists. skip
        return;
    }
    
    map.put(key, hash, value);
}

inline void add_map_entry_vhashmap_no_replace_no_hash(v_map& map, const std::string & key, int value)
{
    if(key.empty()) return;
    char * begin = (char*)key.c_str();
    size_t len = key.length();
    uint64_t hash = value;
    substring search_key = {(char*)key.c_str(), (char*)key.c_str() + len};
    
    if(map.contains(search_key, hash))
    {
        // key already exists. skip
        return;
    }
    
    char * newmem = calloc_or_throw<char>(len);
    memcpy(newmem, begin, len);
    substring insert_key = {newmem, newmem + len};
    map.put(insert_key, hash, value);
}


inline void delete_v_hashmap_entry(substring ss, int)
{
    if(ss.begin != nullptr)
    free(ss.begin);
}
inline void destruct_v_hashmap_entry(v_map_string & map)
{
    // since map.iter()'s parameter is passed by value, we need to work directly off the iterators..
    void * iter = map.iterator();
    while(iter != nullptr)
    {
        v_map_string::hash_elem *elem = (v_map_string::hash_elem *)iter;
        elem->key.~basic_string();
        iter = map.iterator_next(iter);
    }
}

// standard interface maps
template <typename StdIface>
inline void add_map_entry_map_no_replace(StdIface& map, const std::string & key, int value)
{
    if(map.find(key) == map.end()){
        return;
    }
    map[key] = value;
}

static void insert_and_clear_v_hashmap(benchmark::State & state)
{
    v_map map;
    map.set_equivalent(substring_equal);
    for(auto _ : state) {
        for(size_t i = 0; i < inputs.size(); ++i){
            add_map_entry_vhashmap_no_replace(map, inputs[i], i+1);
        }
        map.iter(delete_v_hashmap_entry);
        map.clear();
        benchmark::ClobberMemory();
    }
}
static void insert_and_clear_v_hashmap_string(benchmark::State & state)
{
    v_map_string map;
    map.set_equivalent([](const std::string & a, const std::string & b) -> bool {return a == b;});
    for(auto _ : state) {
        for(size_t i = 0; i < inputs.size(); ++i){
            add_map_entry_vhashmap_no_replace(map, inputs[i], i+1);
        }
        destruct_v_hashmap_entry(map);
        map.clear();
        benchmark::ClobberMemory();
    }
}

static void insert_and_clear_v_hashmap_nohash(benchmark::State & state)
{
    v_map map;
    map.set_equivalent(substring_equal);
    for(auto _ : state) {    
        for(size_t i = 0; i < inputs.size(); ++i){
            add_map_entry_vhashmap_no_replace_no_hash(map, inputs[i], i+1);
        }
        map.iter(delete_v_hashmap_entry);
        map.clear();
        benchmark::ClobberMemory();    
    }
}

static void insert_and_clear_g_densemap(benchmark::State & state)
{
    g_densemap map;
    map.set_empty_key("");
    
    // mimic v_hashmap grow/shrink behavior
    map.max_load_factor(0.25);
    map.min_load_factor(0);
    
    for(auto _ : state){
        for(size_t i = 0; i < inputs.size(); ++i){
            add_map_entry_map_no_replace(map, inputs[i], i+1);
        }
        map.clear_no_resize();
        benchmark::ClobberMemory();
    }
}


static void insert_and_clear_std_hashmap(benchmark::State & state)
{
    std_hashmap map;
    map.max_load_factor(0.25);
    
    for(auto _ : state){
        for(size_t i = 0; i < inputs.size(); ++i){
            add_map_entry_map_no_replace(map, inputs[i], i+1);
        }
        map.clear();
        benchmark::ClobberMemory();
    }
}

static void insert_and_clear_v_hashmap_small(benchmark::State & state)
{
    v_map map;
    map.set_equivalent(substring_equal);
    for(auto _ : state) {    
        for(size_t i = 0; i < SMALL_SIZE; ++i){
            add_map_entry_vhashmap_no_replace(map, inputs[i], i+1);
        }
        map.iter(delete_v_hashmap_entry);
        map.clear();
        benchmark::ClobberMemory();
    }
}

static void insert_and_clear_v_hashmap_small_nohash(benchmark::State & state)
{
    v_map map;
    map.set_equivalent(substring_equal);
    for(auto _ : state) {
        for(size_t i = 0; i < SMALL_SIZE; ++i){
            add_map_entry_vhashmap_no_replace_no_hash(map, inputs[i], i+1);
        }
        map.iter(delete_v_hashmap_entry);
        map.clear();
        benchmark::ClobberMemory();
    }
}
static void insert_and_clear_v_hashmap_small_string(benchmark::State & state)
{
    v_map_string map;
    map.set_equivalent([](const std::string & a, const std::string & b) -> bool {return a == b;});
    //map.init(1023, 0, substring_equal);
    for(auto _ : state) {
        for(size_t i = 0; i < SMALL_SIZE; ++i){
            add_map_entry_vhashmap_no_replace(map, inputs[i], i+1);
        }
        destruct_v_hashmap_entry(map);
        map.clear();
        benchmark::ClobberMemory();
    }
}


static void insert_and_clear_g_densemap_small(benchmark::State & state)
{
    g_densemap map;
    map.set_empty_key("");
    
    // mimic v_hashmap grow/shrink behavior
    map.max_load_factor(0.25);
    map.min_load_factor(0);
    
    for(auto _ : state){
    for(size_t i = 0; i < SMALL_SIZE; ++i){
        add_map_entry_map_no_replace(map, inputs[i], i+1);
    }
    map.clear_no_resize();
    benchmark::ClobberMemory();
    }
}


static void insert_and_clear_std_hashmap_small(benchmark::State & state)
{
    std_hashmap map;
    map.max_load_factor(0.25);
    
    for(auto _ : state){
        for(size_t i = 0; i < SMALL_SIZE; ++i){
            add_map_entry_map_no_replace(map, inputs[i], i+1);
        }
        map.clear();
        benchmark::ClobberMemory();
    }
}

static void v_hashmap_get_values(benchmark::State & state)
{
    v_map map;
    map.set_equivalent(substring_equal);
    for(size_t i = 0; i < inputs.size(); ++i){
        add_map_entry_vhashmap_no_replace(map, inputs[i], i+1);
    }

    substring ss;
    uint64_t hash;
    int val;
    for(auto _ : state){
        for(const auto & str : inputs)
        {
            ss.begin = (char*)str.c_str();
            ss.end = ss.begin + str.length();
            hash = uniform_hash(ss.begin, str.length(), 378401);
            benchmark::DoNotOptimize(val = map.get(ss, hash));
        }
        benchmark::ClobberMemory();
    }
    map.iter(delete_v_hashmap_entry);
    map.clear();
}

static void v_hashmap_get_values_string(benchmark::State & state)
{
    v_map_string map;
    map.set_equivalent([](const std::string & a, const std::string & b) -> bool {return a == b;});
    for(size_t i = 0; i < inputs.size(); ++i){
        add_map_entry_vhashmap_no_replace(map, inputs[i], i+1);
    }

    substring ss;
    uint64_t hash;
    int val;
    for(auto _ : state){
        for(const auto & str : inputs)
        {
            hash = uniform_hash(str.c_str(), str.length(), 378401);
            benchmark::DoNotOptimize(val = map.get(str, hash));
        }
        benchmark::ClobberMemory();
    }
    destruct_v_hashmap_entry(map);
    map.clear();
}


static void g_densemap_get_values(benchmark::State & state)
{
    g_densemap map;
    map.set_empty_key("");
    
    // mimic v_hashmap grow/shrink behavior
    map.max_load_factor(0.25);
    map.min_load_factor(0);

    for(size_t i = 0; i < inputs.size(); ++i){
        add_map_entry_map_no_replace(map, inputs[i], i+1);
    }

    int val;
    for(auto _ : state){
    for(const auto & str : inputs)
    {
        benchmark::DoNotOptimize(val = map[str]);
    }
    benchmark::ClobberMemory();
    }
}
static void std_hashmap_get_values(benchmark::State & state)
{
    std_hashmap map;
    map.max_load_factor(0.25);
    int val;
    for(size_t i = 0; i < inputs.size(); ++i){
        add_map_entry_map_no_replace(map, inputs[i], i+1);
    }
    for(auto _ : state){
        for(const auto & str : inputs)
        {
            benchmark::DoNotOptimize(val = map[str]);
        }
        benchmark::ClobberMemory();
    }
}



BENCHMARK(insert_and_clear_v_hashmap);
BENCHMARK(insert_and_clear_v_hashmap_string);
BENCHMARK(insert_and_clear_v_hashmap_nohash);
BENCHMARK(insert_and_clear_g_densemap);
BENCHMARK(insert_and_clear_std_hashmap);
BENCHMARK(insert_and_clear_v_hashmap_small);
BENCHMARK(insert_and_clear_v_hashmap_small_string);
BENCHMARK(insert_and_clear_v_hashmap_small_nohash);
BENCHMARK(insert_and_clear_g_densemap_small);
BENCHMARK(insert_and_clear_std_hashmap_small);
BENCHMARK(v_hashmap_get_values);
BENCHMARK(v_hashmap_get_values_string);
BENCHMARK(g_densemap_get_values);
BENCHMARK(std_hashmap_get_values);

