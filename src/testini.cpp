#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/foreach.hpp>
#include <string>
#include <set>
#include <exception>
#include <iostream>
namespace pt = boost::property_tree;

struct debug_settings
{
    std::string m_file;               // log filename
    int m_level;                      // debug level
    std::set<std::string> m_modules;  // modules where logging is enabled
    pt::ptree load(const std::string &filename);
    void save(const std::string &filename, pt::ptree);
};

pt::ptree debug_settings::load(const std::string &filename)
{
    // Create empty property tree object
    pt::ptree tree;

    // Parse the INI into the property tree.
    pt::read_ini(filename, tree);

    return tree;
}

void debug_settings::save(const std::string &filename, pt::ptree tree)
{
    // Execute changes on tree
    tree.add("pikachu.color", "Yellow");

    // Write property tree to INI file
    pt::write_ini(filename, tree);
}

int main()
{
    try
    {
        debug_settings ds;
        pt::ptree tree = ds.load("../../runs/run_nepal_2015/test.ini");
        ds.save("../../runs/run_nepal_2015/test_out.ini", tree);
        std::cout << "Success\n";
    }
    catch (std::exception &e)
    {
        std::cout << "Error: " << e.what() << "\n";
    }
    return 0;
}
