#include <iostream>
#include <string>

#include "sqlite3.h"
#include "unique_handle.h"
#include "Diagnostics.h"

using std::string;
using namespace KennyKerr; // unique_handle

/*
    SQLite defines two primary objects:
    - connection object
    - statement object

    SQLite functions return error codes. The most common success code is SQLITE_OK.
*/

// A safe wrapper around the connection object.
struct ConnectionHandleTraits
{
    // The connection pointer type.
    using pointer = sqlite3*;

    static pointer Invalid() throw()
    {
        return nullptr;
    }

    static void Close(pointer value) throw()
    {
        // Verify that sqlite3_close has returned SQLITE_OK.
        VERIFY(SQLITE_OK == sqlite3_close(value));
    }
};

// A type alias for the connection object.
using ConnectionHandle = unique_handle<ConnectionHandleTraits>;

// A safe wrapper around the statement object.
struct StatementHandleTraits
{
    // The statement pointer type.
    using pointer = sqlite3_stmt*;

    static pointer Invalid() throw()
    {
        return nullptr;
    }

    static void Close(pointer value) throw()
    {
        // Verify that sqlite3_finalize has returned SQLITE_OK.
        VERIFY(SQLITE_OK == sqlite3_finalize(value));
    }
};

// A type alias for the statement object.
using StatementHandle = unique_handle<StatementHandleTraits>;

struct SqlException
{
    int Code;
    string Message;

    SqlException(int result, char const * text) :
        Code(result), Message(text)
    {}
};

// The connection class is responsible for one connection handle.
struct Connection
{
    ConnectionHandle handle;

    void Open(char const * filename)
    {
        // Holds a reference to the connection handle.
        auto local = ConnectionHandle{};

        // sqlite3_open creates or opens an existing database file.
        // It returns a handle or a pointer to the database connection through an out parameter.
        // get_address_of returns the address of the underlying pointer. This way, we receive
        // a pointer to a pointer and can effectively place a value directly into the unique_handle.
        auto const result = sqlite3_open(
            filename,
            local.get_address_of());

        // Check if the connection was successfully opened.
        // Keep in mind that even on failure a connection object may be created.
        // It means that we still need to close or delete the connection resource.
        // We deal with that by using the local variable 'local' that holds the connection handle.
        if (SQLITE_OK != result)
        {
            // sqlite3_errmsg returns a UTF-8 character string with an English description of the most recent error
            // on the connection passed as the parameter.
            // We are passing the result of the SQLite error message function to the standard string (SqlException.Message)
            // which makes a copy of it. The value returned by the error message function will automatically be freed when 
            // the SQLite connection object is freed.
            throw SqlException{ result, sqlite3_errmsg(local.get()) };
        }

        // Once we obtained the handle successfully, we can move it into the connection object.
        handle = std::move(local);

        // At this point, we know that we have a valid connection and the destructor will eventually free it. 
    }

    // Executes ad-hoc SQL queries
    void Execute(char const * text)
    {
        // Assert that the handle is valid.
        ASSERT(handle);

        auto const result = sqlite3_exec(
            handle.get(),   // connection handle 
            text,           // SQL command
            nullptr,        // optional callback for each row in the result set
            nullptr,        // optional callback arguments
            nullptr);       // optional error message

        if (SQLITE_OK != result)
        {
            throw SqlException{ result, sqlite3_errmsg(handle.get()) };
        }
    }
};

struct Statement
{
    // The handle takes care of closing or freeing the statement.
    StatementHandle handle;

    // Compile the statement to byte code.
    void Prepare(Connection const & conn, char const * text)
    {
        // Reset the handle so it could be reused for multiple SQL statements.
        handle.reset();

        // Create the handle to the statement. Unlike opening a connection, the prepare function does not 
        // return a pointer or a handle if it fails to complete the statement.
        auto const result = sqlite3_prepare_v2(
            conn.handle.get(),          // connection handle
            text,                       // SQL statement to compile
            strlen(text),               // the length of the statement in bytes
            handle.get_address_of(),    // the resulting statement handle; if this fails it will be a null pointer value
            nullptr);                   // an optional pointer to the end of the statement

        if (SQLITE_OK != result)
        {
            // Use the connection object to retrieve the error message.
            throw SqlException{ result, sqlite3_errmsg(conn.handle.get()) };
        }
    }

    // Evaluate the compiled (prepared) statement.
    bool Step()
    {
        // Assert that the statement is valid.
        ASSERT(handle);

        // Evaluate the statement. The retured value depends on the statement being evaluated:
        // - if the statement returns no data, then the result is the SQLITE_DONE constant on success
        // - otherwise, the SQLITE_ROW constant is returned for rows of data from repeated calls until the result set is exhausted and SQLLITE_DONE is returned
        auto const result = sqlite3_step(handle.get());

        // Return true if one or more rows are available.
        if (result == SQLITE_ROW) return true;

        // Return false if execution has come to an end.
        if (result == SQLITE_DONE) return false;

        // In all other cases something must have gone wrong.
        // To retrieve the error message we need the connection object but fortunately, SQLite provides a function 
        // to retrieve the connection for a statement. 
        throw SqlException{ result, sqlite3_errmsg(sqlite3_db_handle(handle.get())) };
    }

    // Retrieve an integer column value.
    auto GetInt(int const column = 0) -> int
    {
        return sqlite3_column_int(handle.get(), column);
    }

    // Retrieve a string column value.
    auto GetString(int const column = 0) -> char const *
    {
        // The column function returns an unsigned character string rather than a plain character string (? what is a plain character string?).
        // The statement takes care of the allocation. It means we don't need to worry about freeing the string but we need to grab 
        // a copy before closing the statement, as it will be invalidated. 
        return reinterpret_cast<char const *>(sqlite3_column_text(handle.get(), column));
    }
};

int main()
{
    try
    {
        // Create a connection object that's initially disconnected.
        Connection conn;

        // Create or open a database and establishing a connection to it.
        conn.Open("C:\\Temp\\Test.db");

        conn.Execute("DROP TABLE Book");
        conn.Execute("CREATE TABLE Book (Id INT PRIMARY KEY, Title NVARCHAR(100) NOT NULL)");
        conn.Execute("INSERT INTO Book (Id, Title) VALUES (1, 'A'), (2, 'B'), (3, 'C')");

        Statement s;

        s.Prepare(conn, "SELECT Id FROM Book WHERE Title = 'B'");
        if (s.Step())
        {
            TRACE(L"Id: %d\n", s.GetInt());
        }

        s.Prepare(conn, "SELECT Title FROM Book WHERE Id = 3");
        if (s.Step())
        {
            TRACE(L"Title: %S\n", s.GetString());
        }

        s.Prepare(conn, "SELECT Id, Title FROM Book ORDER BY Id DESC");
        while (s.Step()) // call Step in a loop to retrieve all rows
        {
            TRACE(L"%d %S\n", s.GetInt(0), s.GetString(1));
        }
    }
    catch (SqlException const & e)
    {
        TRACE(L"%d %S\n", e.Code, e.Message.c_str());
    }
}
