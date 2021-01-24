// Copyright 2021 ykvopich <Kravchenko_vlad2001@bk.ru>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <iostream>
#include <boost/filesystem.hpp>
#include <sstream>
#include <map>
#include <utility>
#include <vector>

using std::string;
using std::cout;
using std::vector;
using std::runtime_error;
using std::ostream;
using std::stringstream;
using std::make_pair;
using std::find_if;


class Broker {
 private:

  class Account {
   private:

    std::string lastDate;
    size_t fileNum{};

   public:

    inline static void setDate(Account& acc, const std::string& date) {
      acc.fileNum++;
      if (atoi(date.c_str()) > atoi(acc.lastDate.c_str())) {
        acc.lastDate = date;
      }
    }
    Account() = default;
    explicit Account(std::string date)
        : lastDate(std::move(date)), fileNum(0){};
    [[nodiscard]] size_t getFileNum() const { return fileNum; }
    [[nodiscard]] std::string getLastDate() const { return lastDate; }
  };

  std::map<std::string, Account> accounts;
  std::string name;

 public:

  static Broker CheckBroker(const boost::filesystem::path& p);
  explicit Broker(std::string n) : name(std::move(n)) {}
  friend std::ostream& operator<<(std::ostream& os,
                                  const std::vector<Broker>& brokers);
  static std::vector<Broker> Checking(const boost::filesystem::path& p,
                                     std::ostream& os);
  inline static bool isRightFile(const boost::filesystem::path& fileName);
};

inline bool is_separator(char c) { return c == '_'; }
inline bool not_separator(char c) { return !is_separator(c); }

#endif // INCLUDE_HEADER_HPP_
