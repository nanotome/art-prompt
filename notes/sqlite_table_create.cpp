#include <sqlite3.h>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
    /**
    Access SQlite db to write all emoji svgs into the sqlite db
    */
    sqlite3* db;
    int rc;  // holds the output of SQLite executions; 0 is success; higher is
             // error
    char* zErrMsg = 0;  // holds the error message of a failed SQLite execution;
                        // must be passed into the call as a reference

    std::string masterDataTableSQL;  // container for sqlite statement to create
                                     // master_data table
    std::string
        jobsTableSQL;  // container for sqlite statement to create jobs table
    std::string masterDataInsertSQL;  // container for sqlite statement to
                                      // insert data into master_data table
    std::string jobsInsertSQL;  // container for sqlite statement to insert data
                                // into jobs table

    rc = sqlite3_open("../ranmoji.db", &db);

    if (rc)
    {
        std::cerr << "Unable to open database" << sqlite3_errmsg(db)
                  << std::endl;
        return 0;
    }

    std::cout << "Opened database successfully" << std::endl;

    // sqlite statement as raw string; best practice is to use a
    // prepared_statement id table must be autoincrement if not null or an error
    // will be thrown
    masterDataTableSQL =
        "CREATE TABLE master_data("
        "id int primary key autoincrement not null,"
        "emoji_id varchar(255) not null,"
        "svg text not null);";

    jobsTableSQL =
        "CREATE TABLE jobs("
        "id int primary key autoincrement not null,"
        "emoji_id varchar(255) not null,"
        "svg text not null,"
        "status varchar(50) not null default 'NEW',"
        "startedAt DATE,"
        "finishedAt DATE);";

    // sqlite3_exec requires a C-string for the statement to we convert via
    // .c_str()
    // zErrMsg is passed in via reference so the error result is stored into it.
    // Failure to do so results in a segmentation fault error when trying to
    // cout the error message
    rc = sqlite3_exec(db, masterDataTableSQL.c_str(), nullptr, nullptr,
                      &zErrMsg);

    if (rc != SQLITE_OK)
    {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }
    else
    {
        std::cout << "Master table created successfully" << std::endl;
    }

    rc = sqlite3_exec(db, jobsTableSQL.c_str(), nullptr, nullptr, &zErrMsg);

    if (rc != SQLITE_OK)
    {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }
    else
    {
        std::cout << "Jobs table created successfully" << std::endl;
    }

    std::vector<std::string> emojiPaths;
    const std::filesystem::path emojis{ "../images/svg" };
    // iterate over all the files in the '../images/svg' directory
    for (const auto& entry : std::filesystem::directory_iterator{ emojis })
    {
        emojiPaths.push_back(entry.path());
        std::ifstream svgFile(entry.path());
        std::string fileLine;
        std::string svgText;

        while (std::getline(svgFile, fileLine))
        {
            svgText += fileLine;
        }

        std::cout << "Inserting SVG:" << std::endl;
        std::cout << entry.path() << std::endl;

        // insert into db here
        // raw string; best practice is to use a prepared statement with
        // parameters
        masterDataInsertSQL =
            "insert into master_data (emoji_id,svg) values(\"" +
            entry.path().string() + "\",\"" + svgText + "\");";
        jobsInsertSQL = "insert into jobs (emoji_id,svg) values(\"" +
                        entry.path().string() + "\",\"" + svgText + "\");";

        rc = sqlite3_exec(db, masterDataInsertSQL.c_str(), nullptr, nullptr,
                          &zErrMsg);
        if (rc != SQLITE_OK)
        {
            std::cerr << "Master data insert SQL error: " << zErrMsg
                      << std::endl;
            sqlite3_free(zErrMsg);
        }

        rc =
            sqlite3_exec(db, jobsInsertSQL.c_str(), nullptr, nullptr, &zErrMsg);

        if (rc != SQLITE_OK)
        {
            std::cerr << "Jobs insert SQL error: " << zErrMsg << std::endl;
            sqlite3_free(zErrMsg);
        }
    }

    std::random_device dev;
    std::mt19937 randomness_generator(dev());
    std::uniform_int_distribution<std::size_t> index_distribution(
        0, emojiPaths.size());

    auto i = index_distribution(randomness_generator);
    const std::string randomEmoji = emojiPaths[i];

    return 0;
}
