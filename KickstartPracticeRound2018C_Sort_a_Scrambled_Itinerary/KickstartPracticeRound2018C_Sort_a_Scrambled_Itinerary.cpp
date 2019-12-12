#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <string>

using namespace std;

struct ll
{
    struct ll *prev = nullptr;
    struct ll *next = nullptr;
    list<string> itinerary;
} *root;

map<string, struct ll*> departure;              // Use std::map which is always sorted
map<string, struct ll*> arrival;

void solve()
{
    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
        string d, a;
        cin >> d >> a;

        struct ll *prev, *next;

        try { prev = arrival.at(d); }           // Is there any itinerary that arrives at d?
        catch (...) { prev = nullptr; }         // It not, gets here.

        try { next = departure.at(a); }         // Is there any itinerary that departs from a?
        catch (...) { next = nullptr; }         // If not, gets here.

        if (!prev && !next) {                   // new itinerary
            struct ll* elem = new struct ll;
            elem->itinerary.emplace_front(d);
            elem->itinerary.emplace_back(a);

            // insert at the front of linked list
            if (root) {
                // linked list not empty
                elem->next = root;
                root->prev = elem;
            }
            root = elem;

            departure.emplace(d, elem);
            arrival.emplace(a, elem);
        } else if (!prev && next) {             // only a matches one of departures
            next->itinerary.emplace_front(d);
            departure.erase(a);
            departure.emplace(d, next);
        } else if (prev && !next) {             // only d matches one of arrivals
            prev->itinerary.emplace_back(a);
            arrival.erase(d);
            arrival.emplace(a, prev);
        } else {                                // merge two itineraries
            prev->itinerary.splice(prev->itinerary.end(), next->itinerary);
            departure.erase(a);
            arrival.erase(d);
            arrival.erase(prev->itinerary.back());
            arrival.emplace(prev->itinerary.back(), prev);

            // We don't need "next" any more.
            // Delete it from the linked list ...
            if (next == root) {
                root = next->next;
                root->prev = nullptr; // it is safe to assume that root->prev != nullptr
            } else {
                next->prev->next = next->next;
                if (next->next)
                    next->next->prev = next->prev;
            }

            // ... and return memory assigned to it.
            delete next;
        }
    }

    list<string> ans = root->itinerary;

    for (int i = 0; i < N; i++) {
        cout << " " << ans.front();
        ans.pop_front();
        cout << "-" << ans.front();
    }
    cout << endl;

    // If nothing goes wrong, there should be only one item left
    // in "departure" and "arrival" each.
    departure.erase(root->itinerary.front());
    arrival.erase(root->itinerary.back());

    delete root;
    root = nullptr;
}

int main()
{
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        cout << "Case #" << to_string(i) << ":";
        solve();
    }
}