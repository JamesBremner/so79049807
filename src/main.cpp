#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
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
    int myInitRes1;
    int myInitRes2;
    int myUsedmyRes1; // Used CPU in this bin
    int myUsedmyRes2; // Used RAM in this bin
    int myUtilRes1;
    int myUtilRes2;

    cThing(const std::string name)
        : myName(name),
          myPacked(false)
    {
    }

    void set(int res1, int res2)
    {
        myInitRes1 = res1;
        myInitRes2 = res2;
        myRes1 = res1;
        myRes2 = res2;
    }
    std::string text() const
    {
        std::stringstream ss;
        ss << myName << " " << myRes1 << " " << myRes2 << "\n";
        return ss.str();
    }

    void ContentsDisplay();

    void utilDisplay();

    bool pack(cThing &item);

    void utilization();
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
        bin.set(
            optRes[rand() % 4 + 4],
            optRes[rand() % 5 + 4]);
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

void cThing::utilDisplay()
{
    std::cout << std::setw(10) << myName
              << std::setw(15) << myUsedmyRes1
              << std::setw(15) << myUsedmyRes2
              << std::setw(10) << myInitRes1
              << std::setw(10) << myInitRes2
              << std::setw(16) << myUtilRes1
              << std::setw(16) << myUtilRes2
              << "\n";
}

bool cThing::pack(cThing &item)
{
    myRes1 -= item.myRes1;
    myRes2 -= item.myRes2;
    item.myPacked = true;
    myItems.push_back(item.myName);

    return true;
}

void cThing::utilization()
{
    myUsedmyRes1 = 0;
    myUsedmyRes2 = 0;
    for (auto &itemName : myItems)
    {
        auto it = std::find_if(
            theItems.begin(), theItems.end(),
            [&](const cThing &i)
            {
                return i.myName == itemName;
            });
        if (it == theItems.end())
            continue;
        myUsedmyRes1 += it->myRes1;
        myUsedmyRes2 += it->myRes2;
    }
    myUtilRes1 = (int)(100 * myUsedmyRes1 / myInitRes1);
    myUtilRes2 = (int)(100 * myUsedmyRes2 / myInitRes2);
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

            bin.pack(item);

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

void print_node_utilization()
{
    std::cout << "\nTotal CPU and RAM % utilization for each node:\n";
    std::cout << std::setw(10) << "Node"
              << std::setw(15) << "Total_CPU_Used"
              << std::setw(15) << "Total_RAM_Used"
              << std::setw(10) << "Node_CPU"
              << std::setw(10) << "Node_RAM"
              << std::setw(16) << "CPU_Utilization"
              << std::setw(16) << "RAM_Utilization" << "\n";

    // Sort the node data by node names
    std::sort(
        theBins.begin(), theBins.end(),
        [](const cThing &a, const cThing &b)
        {
            return a.myName < b.myName; // Sort by node name
        });

    // calculate the resource utilization for each bin
    for (auto &bin : theBins)
    {
        bin.utilization();
        bin.utilDisplay();
    }
}

main()
{
    create_pods_and_nodes(40, 4);
    text();
    pack();
    packDisplay();
    print_node_utilization();
    return 0;
}
