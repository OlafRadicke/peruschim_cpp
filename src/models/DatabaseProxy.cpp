#include "DatabaseProxy.h"

# define DEBUG cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
# define ERROR cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<


using namespace std;


string DatabaseProxy::convertIntToStr( int number )
{
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

vector< vector<string> > DatabaseProxy::sqlGet ( string sqlcommand )
{
    Config config;
    vector< vector<string> >  list_2d;
    unsigned int     col_count;

    string conn_para = config.get( "DB-DRIVER" );
    tntdb::Connection conn;
    tntdb::Result result;

    conn = tntdb::connect(conn_para);
    DEBUG "SQLCODE: " << sqlcommand << endl;
    result = conn.select( sqlcommand );
    for (tntdb::Result::const_iterator it = result.begin();
        it != result.end(); ++it
    ) {
        vector<string>  list_1d;
        tntdb::Row row = *it;
        for ( col_count = 0; col_count != row.size(); col_count++ ) {
            std::string value;
            row[col_count].get(value);
            string copy_value = value;
            list_1d.push_back( copy_value );
        }
        list_2d.push_back( list_1d );
    }
    conn.close();
    return list_2d;
}

string DatabaseProxy::sqlGetSingle ( string sqlcommand )
{
    Config config;
    unsigned int     col_count;

    string conn_para = config.get( "DB-DRIVER" );
    tntdb::Connection conn;
    tntdb::Result result;

    conn = tntdb::connect( conn_para );
    result = conn.select( sqlcommand );
    for (tntdb::Result::const_iterator it = result.begin();
        it != result.end(); ++it
    ) {
        tntdb::Row row = *it;
        for ( col_count = 0; col_count != row.size(); col_count++ ) {

            std::string value;
            row[col_count].get(value);
            DEBUG "value=" << value << endl;
            return value;
        }
    }
    return "";
}

void DatabaseProxy::sqlSet ( string sqlcommand )
{
    Config config;
    DEBUG "sqlcommand: " << sqlcommand << endl;

    string conn_para = config.get( "DB-DRIVER" );
    tntdb::Connection conn;
    tntdb::Result result;

    conn = tntdb::connect( conn_para );
    conn.execute( sqlcommand );

}


std::string DatabaseProxy::replace (  std::string s ){
    if ( s == "" ) {
        return "";
    }
    return DatabaseProxy::replace ( s, "'", "\\'" );
}

std::string DatabaseProxy::replace (
    std::string s,
    const std::string& k,
    const std::string& r
){
    if ( s.length() == 0 ) {
        return s;
    }
    std::string::size_type p = 0;
    p = s.find(k, p);
    while ( p != std::string::npos) {
        s.replace(p, k.length(), r);
        p += r.length();
        p = s.find(k, p);
    }
    return s;
}


