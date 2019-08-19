#include "v_hashmap.h"
#include "hash.h"
#include "parse_primitives.h"
#include "memory.h"
#include "sparsehash/dense_hash_map"
#include <boost/utility/string_view.hpp>
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

using boost::string_view;


static void substring_from_string(benchmark::State & state)
{
    char * begin;
    for(auto _ : state){
        for(const auto & str : inputs)
        {
            substring ss = {const_cast<char*>(str.c_str()), const_cast<char*>(str.c_str())+str.length()};
            benchmark::DoNotOptimize(begin = ss.begin);
            benchmark::ClobberMemory();
        }
    }
}

static void string_view_from_string(benchmark::State & state)
{
    const char * begin;
    for(auto _ : state){
        for(const auto & str : inputs)
        {
            string_view sv(str);
            benchmark::DoNotOptimize(begin = sv.begin());
            benchmark::ClobberMemory();
        }
    }
}


static void substring_from_string_prefix_suffix(benchmark::State & state)
{
    char * begin;
    for(auto _ : state){
        for(const auto & str : inputs)
        {
            substring ss = {const_cast<char*>(str.c_str()), const_cast<char*>(str.c_str())+str.length()};
            if(str.length() >= 2)
            {
                ss.begin += 2;                
            }
            if(str.length() >= 4)
            {
                ss.end -= 2;
            }
            benchmark::DoNotOptimize(begin = ss.begin);
            benchmark::ClobberMemory();
        }
    }
}


static void string_view_from_string_prefix_suffix(benchmark::State & state)
{
    const char * begin;
    for(auto _ : state){
        for(const auto & str : inputs)
        {
            string_view sv(str);
            // remove_prefix and remove_suffix does length checking
            sv.remove_prefix(2);
            sv.remove_suffix(2);
            benchmark::DoNotOptimize(begin = sv.begin());
            benchmark::ClobberMemory();
        }
    }
}

static void string_view_from_string_prefix_suffix2(benchmark::State & state)
{
    const char * begin;
    for(auto _ : state){
        for(const auto & str : inputs)
        {
            const char * b = str.length() >= 2 ? str.c_str()+2 : str.c_str();
            string_view sv(b, str.length() - 4);
            benchmark::DoNotOptimize(begin = sv.begin());
            benchmark::ClobberMemory();
        }
    }
}

static void substring_from_string_copy(benchmark::State & state)
{
    char * begin;
    for(auto _ : state){
        for(const auto & str : inputs)
        {
            substring ss;
            ss.begin = calloc_or_throw<char>(str.length()+1);
            ss.end = ss.begin + str.length()+1;
            memcpy(ss.begin, str.c_str(), str.length());
            benchmark::DoNotOptimize(begin = ss.begin);
            free(ss.begin);
            benchmark::ClobberMemory();
        }
    }
}

static void string_from_string(benchmark::State & state)
{
    const char * begin;
    for(auto _ : state){
        for(const auto & str : inputs)
        {
            std::string s(str);
            benchmark::DoNotOptimize(begin = &*s.begin());
            benchmark::ClobberMemory();
        }
    }
}


static void substring_to_substring(benchmark::State & state)
{
    char * begin;
    std::vector<substring> ss_vector;
    ss_vector.reserve(inputs.size());
    for(const auto & str : inputs)
    {
        substring ss = {const_cast<char*>(str.c_str()), const_cast<char*>(str.c_str())+str.length()};
        ss_vector.push_back(ss);
    }
    for(auto _ : state){
        for(const auto & ss : ss_vector){
            substring ss2 = ss;
            benchmark::DoNotOptimize(begin = ss2.begin);
            benchmark::ClobberMemory();
        }
    }
}

static void string_view_to_string_view(benchmark::State & state)
{
    const char * begin;
    std::vector<string_view> sv_vector;
    sv_vector.reserve(inputs.size());
    for(const auto & str : inputs)
    {
        sv_vector.emplace_back(str);
    }
    for(auto _ : state){
        for(const auto & sv : sv_vector){
            string_view sv2(sv);
            benchmark::DoNotOptimize(begin = sv2.begin());
            benchmark::ClobberMemory();
        }
    }
}

static void substring_to_string(benchmark::State & state)
{
    int len;
    std::vector<substring> ss_vector;
    ss_vector.resize(inputs.size());
    for(const auto & str : inputs)
    {
        substring ss = {const_cast<char*>(str.c_str()), const_cast<char*>(str.c_str())+str.length()};
        ss_vector.push_back(ss);
    }
    for(auto _ : state){
        for(const auto & ss : ss_vector){
            std::string s(ss.begin, ss.end-ss.begin);
            benchmark::DoNotOptimize(len = s.length());
            benchmark::ClobberMemory();
        }
    }
}

static void string_view_to_string(benchmark::State & state)
{
    int len;
    std::vector<string_view> sv_vector;
    sv_vector.resize(inputs.size());
    for(const auto & str : inputs)
    {
        sv_vector.emplace_back(str);
    }
    for(auto _ : state){
        for(const auto & sv : sv_vector){
            std::string s(sv.begin(), sv.length());
            benchmark::DoNotOptimize(len = s.length());
            benchmark::ClobberMemory();
        }
    }
}


BENCHMARK(substring_from_string);
BENCHMARK(string_view_from_string);
BENCHMARK(substring_from_string_prefix_suffix);
BENCHMARK(string_view_from_string_prefix_suffix);
BENCHMARK(string_view_from_string_prefix_suffix2);
BENCHMARK(substring_from_string_copy);
BENCHMARK(string_from_string);

BENCHMARK(substring_to_substring);
BENCHMARK(string_view_to_string_view);
BENCHMARK(substring_to_string);
BENCHMARK(string_view_to_string);
