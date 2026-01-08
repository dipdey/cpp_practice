/**
 * https://leetcode.com/problems/design-a-food-rating-system/description/
 * Design a Food Rating System
 */
#include <vector>
#include <iostream>
#include <sstream>
#include <map>
#include "plugin_api.h"


static PluginInfo info {
    "2353",
    "Design a Food Rating System",
    PLUGIN_API_VERSION
};

typedef struct _Food
{
    _Food(std::string _name, std::string _cuisine, int _rating)
    {
        name = _name;
        cuisine = _cuisine;
        rating = _rating;
        index = -1;
    }
    std::string name;
    std::string cuisine;
    int rating;
    int index;
} Food;

class MaxHeap
{
public:
    MaxHeap() : heap_size(0) {}
    void push(Food *food);
    void update(Food *food, int new_rating);
    Food *top();

private:
    int heap_size;
    std::vector<Food *> heap;

    void heapifyUp(int i);
    void heapifyDown(int i);
};

Food *MaxHeap::top()
{
    if (heap.size() > 0)
    {
        return heap[0];
    }
    return NULL;
}

void MaxHeap::push(Food *food)
{
    heap.push_back(food);
    heap_size = heap.size();
    food->index = heap_size - 1;
    heapifyUp(food->index);
}

void MaxHeap::update(Food *food, int new_rating)
{
    int old_rating = food->rating;
    food->rating = new_rating;
    if (new_rating > old_rating)
    {
        // move up
        heapifyUp(food->index);
    }
    else if (new_rating < old_rating)
    {
        heapifyDown(food->index);
    }
    else
    {
        // do nothing
    }
}

void MaxHeap::heapifyDown(int i)
{
    if (i < heap_size - 1)
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;
        if (left < heap_size && ((heap[largest]->rating < heap[left]->rating) ||
            (heap[largest]->rating == heap[left]->rating && heap[largest]->name.compare(heap[left]->name) > 0)))
        {
            largest = left;
        }
        if (right < heap_size && ((heap[largest]->rating < heap[right]->rating) ||
            (heap[largest]->rating == heap[right]->rating && heap[largest]->name.compare(heap[right]->name) > 0)))
        {
            largest = right;
        }
        if (largest != i)
        {
            // swap
            Food *tmp = heap[i];
            heap[i] = heap[largest];
            heap[largest] = tmp;
            // adjust the index
            int idx = heap[i]->index;
            heap[i]->index = heap[largest]->index;
            heap[largest]->index = idx;
            heapifyDown(largest);
        }
    }
}

void MaxHeap::heapifyUp(int i)
{
    if (i > 0)
    {
        int parent = (i - 1) / 2;
        if (i != parent)
        {
            if ((heap[i]->rating > heap[parent]->rating) ||
                (heap[i]->rating == heap[parent]->rating && heap[i]->name.compare(heap[parent]->name) < 0))
            {
                // swap
                Food *tmp = heap[i];
                heap[i] = heap[parent];
                heap[parent] = tmp;
                // adjust the index
                int idx = heap[i]->index;
                heap[i]->index = heap[parent]->index;
                heap[parent]->index = idx;
                // recur up
                heapifyUp(parent);
            }
        }
    }
}

class FoodRatings
{
public:
    FoodRatings(std::vector<std::string> &foods, std::vector<std::string> &cuisines, std::vector<int> &ratings)
    {
        for (int i = 0; i < foods.size(); ++i)
        {
            Food *f = new Food(foods[i], cuisines[i], ratings[i]);
            foods_map.insert(std::pair<std::string, Food *>(f->name, f));
            if (cuisine_map.find(cuisines[i]) == cuisine_map.end())
            {
                cuisine_map[cuisines[i]] = new MaxHeap();
            }
            cuisine_map[cuisines[i]]->push(f);
        }
    }

    void changeRating(std::string food, int newRating)
    {
        std::map<std::string, Food *>::iterator it = foods_map.find(food);
        if (it != foods_map.end())
        {
            cuisine_map[it->second->cuisine]->update(it->second, newRating);
        }
    }

    std::string highestRated(std::string cuisine)
    {
        std::string ret = "";
        std::map<std::string, MaxHeap *>::iterator it = cuisine_map.find(cuisine);
        if (it != cuisine_map.end())
        {
            Food *f = it->second->top();
            ret = f != NULL ? f->name : "";
        }
        return ret;
    }

private:
    std::map<std::string, Food *> foods_map;
    std::map<std::string, MaxHeap *> cuisine_map;
};

static void test_case1()
{
    std::vector<std::string> foods = {"kimchi", "miso", "sushi", "moussaka", "ramen", "bulgogi"};
    std::vector<std::string> cuisine = {"korean", "japanese", "japanese", "greek", "japanese", "korean"};
    std::vector<int> ratings = {9, 12, 8, 15, 14, 7};
    FoodRatings foodRatings(foods, cuisine, ratings);
    std::cout << foodRatings.highestRated("korean") << std::endl;
    std::cout << foodRatings.highestRated("japanese") << std::endl;
    foodRatings.changeRating("sushi", 16);
    std::cout << foodRatings.highestRated("japanese") << std::endl;
    foodRatings.changeRating("ramen", 16);
    std::cout << foodRatings.highestRated("japanese") << std::endl;
}

static void test_case2()
{
    std::vector<std::string> foods = {"pwdgjvphy","tiwlr","mqpdbl","jjhmgnxt","dmlymzufx"};
    std::vector<std::string> cuisine = {"dsyujtjljz","eluxblkt","dsyujtjljz","dsyujtjljz","eluxblkt"};
    std::vector<int> ratings = {15,10,5,16,18};
    FoodRatings foodRatings(foods, cuisine, ratings);
    std::cout << foodRatings.highestRated("dsyujtjljz") << std::endl;
    std::cout << foodRatings.highestRated("eluxblkt") << std::endl;
    foodRatings.changeRating("dmlymzufx",14);
    foodRatings.changeRating("tiwlr",11);
    std::cout << foodRatings.highestRated("eluxblkt") << std::endl;
    foodRatings.changeRating("tiwlr",8);
    std::cout << foodRatings.highestRated("eluxblkt") << std::endl;
    std::cout << foodRatings.highestRated("dsyujtjljz") << std::endl;
    std::cout << foodRatings.highestRated("dsyujtjljz") << std::endl;
    std::cout << foodRatings.highestRated("eluxblkt") << std::endl;
}

extern "C" {

PLUGIN_API PluginInfo* plugin_info() {
    return &info;
}

PLUGIN_API void plugin_do_test(void) {
    test_case2();
}
}