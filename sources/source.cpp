// Copyright 2021 ykvopich <kravchenko_vald2001@bk.ru>

#include <Broker.hpp>

void FilenameToString(const string &text, string& ID, string& date) {
  vector<string> fromFile;
  for (auto i = text.cbegin(); i != text.cend();) {
    i = find_if(i, text.end(), not_separator);
    auto j = find_if(i, text.end(), is_separator);
    fromFile.emplace_back(i, j);
    i = j;
  }
  if (fromFile.size() == 3) {
    ID = fromFile[1];
    date = fromFile[2];
  }
}

Broker Broker::CheckBroker(const boost::filesystem::path &p) {
  Broker broker(p.filename().string());
  for (const auto& x : boost::filesystem::directory_iterator{p})
  {
    if(!is_directory(x)) {
      if (isRightFile(x.path())) {
        string accountID;
        string accountDate;

        FilenameToString(x.path().stem().string(), accountID, accountDate);

        if(broker.accounts.find(accountID) != broker.accounts.end()) {
          Account::setDate(broker.accounts[accountID], accountDate);
        } else {
          broker.accounts.insert(make_pair<string, Account>(accountID.c_str(), Account(accountDate)));
        }
      }
    }
  }
  return broker;
}

vector<Broker> Broker::Checking(const boost::filesystem::path& p, ostream& os) {
  vector<Broker> bData;
  if (!boost::filesystem::is_directory(p))
    throw runtime_error(
        "argument must be path to Broker directory, not file");
  for (const auto& x : boost::filesystem::directory_iterator{p})
  {
    if(!is_directory(x)) {
      if (isRightFile(x.path())) {
        os << x.path().filename().string() << "\n";
      }
    } else if (is_directory(x)) {
      stringstream out;
      out << x.path().filename().string() << "\n";
      Checking(x.path(), out);
      if(out.str() != x.path().filename().string() + "\n"){
        os << out.str();
        bData.emplace_back(Broker::CheckBroker(x.path()));
      }
    } else {
      os << "This is not a regular file or dir!\n";
    }
  }
  return bData;
}

ostream &operator<<(ostream &os, const vector<Broker>& brokers) {
  if (brokers.empty()) {
    os << "Brokers array is empty!\n";
  } else {
    os <<"\n";
    for (const auto& broker : brokers) {
      for (const auto& account : broker.accounts) {
        os << "broker:" << broker.name + "\t"
           << "account:" << account.first << "\tfiles:" << account.second.getFileNum()
           << "\tlastdate:" << account.second.getLastDate() << "\n";
      }
    }
  }
  return os;
}

bool Broker::isRightFile(const boost::filesystem::path &fileName) {
  return (fileName.stem().extension().string() != ".old" &&
          fileName.filename().string().find("balance") != string::npos);
}
