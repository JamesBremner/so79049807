#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

class cThing
{
public:
    std::string myName;
    int myRes1;
    int myRes2;
    bool myPacked;
    std::vector<std::string> myItems;

    cThing(const std::string name)
        : myName(name),
          myPacked(false)
    {
    }
    std::string text() const
    {
        std::stringstream ss;
        ss << myName << " " << myRes1 << " " << myRes2 << "\n";
        return ss.str();
    }

    void ContentsDisplay();

    bool pack(cThing &item);
};

std::vector<cThing> theItems;
std::vector<cThing> theBins;

void create_pods_and_nodes(int n_pods = 40, int n_nodes = 15)
{
    // # Create pod and node names
    // pod = ['pod_' + str(i+1) for i in range(n_pods)]
    // node = ['node_' + str(i+1) for i in range(n_nodes)]

    for (int i = 0; i < n_pods; i++)
        theItems.emplace_back("pod_" + std::to_string(i + 1));
    for (int i = 0; i < n_nodes; i++)
        theBins.emplace_back("node_" + std::to_string(i + 1));

    // #Create the pods DataFrame
    //     pods = pd.DataFrame({
    //         'pod': pod,
    //         'cpu': random.choices(cpu[0:3], k=n_pods),  # Small CPU for pods
    //         'ram': random.choices(ram[0:4], k=n_pods),  # Small RAM for pods
    //     # Create the nodes DataFrame
    // nodes = pd.DataFrame({
    //     'node': node,
    //     'cpu': random.choices(cpu[4:len(cpu)-1], k=n_nodes),  # Larger CPU for nodes
    //     'ram': random.choices(ram[4:len(ram)-1], k=n_nodes),  # Larger RAM for nodes

    std::vector<int> optRes;
    for (int i = 1; i < 10; i++)
        optRes.push_back(pow(2, i));

    for (auto &item : theItems)
    {
        item.myRes1 = optRes[rand() % 3];
        item.myRes2 = optRes[rand() % 4];
    }
    for (auto &bin : theBins)
    {
        bin.myRes1 = optRes[rand() % 4 + 4];
        bin.myRes2 = optRes[rand() % 5 + 4];
    }
}

void text()
{
    std::cout << "items\n";
    for (auto &t : theItems)
        std::cout << t.text();

    std::cout << "bins\n";
    for (auto &t : theBins)
        std::cout << t.text();
}

void cThing::ContentsDisplay()
{
    if (!myItems.size())
    {
        std::cout << myName << " is empty\n";
        return;
    }
    std::cout << myName << " contains: ";
    for (auto &n : myItems)
        std::cout << n << " ";
    std::cout << "\n";
}

bool cThing::pack(cThing &item)
{
    myRes1 -= item.myRes1;
    myRes2 -= item.myRes2;
    item.myPacked = true;
    myItems.push_back(item.myName);

    return true;
}

void pack()
{
    // sort items in order of decreasing largest resource requirement sum

    std::sort(
        theItems.begin(), theItems.end(),
        [](const cThing &a, const cThing &b) -> bool
        {
            int sa = a.myRes1 + a.myRes2;
            int sb = b.myRes1 + b.myRes2;
            return sa > sb;
        });

    // sort bins in order of increasing capacity sum

    std::sort(
        theBins.begin(), theBins.end(),
        [](const cThing &a, const cThing &b) -> bool
        {
            int sa = a.myRes1 + a.myRes2;
            int sb = b.myRes1 + b.myRes2;
            return sa < sb;
        });

    // fit each item into the smallest bin that fits
    
    for (cThing &item : theItems)
    {
        for (cThing &bin : theBins)
        {
            if (item.myRes1 > bin.myRes1 ||
                item.myRes2 > bin.myRes2)
            continue;

            bin.pack( item );

            break;
        }
    }
}
void packDisplay()
{
    int unpackedCount = 0;
    for (auto &item : theItems)
    {
        if (!item.myPacked)
        {
            std::cout << item.myName << " ";
            unpackedCount++;
        }
    }
    std::cout << "\n";
    if (!unpackedCount)
        std::cout << "All iems packed\n";
    else
        std::cout << unpackedCount << " items did not fit\n";

    for (auto &bin : theBins)
        bin.ContentsDisplay();
}

main()
{
    create_pods_and_nodes(40, 4);
    text();
    pack();
    packDisplay();
    return 0;
}
