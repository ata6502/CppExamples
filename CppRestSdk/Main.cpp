#include <iostream>
#include <conio.h> // getch()

using std::cout;

/*
    Github: https://github.com/Microsoft/cpprestsdk
    Getting started: https://github.com/Microsoft/cpprestsdk/wiki/Getting-Started-Tutorial
    Wiki: https://github.com/Microsoft/cpprestsdk/wiki
    Getting the C++ REST SDK on Windows: PS> vcpkg install cpprestsdk cpprestsdk:x64-windows
*/

#include <cpprest\json.h>
#include <cpprest\http_client.h>

void SerializeJson()
{
    web::json::value v;
    v[L"Name"] = web::json::value::string(U("Test"));
    v[L"Number"] = web::json::value::number(8);

    std::wstring str = v.serialize();
    std::wcout << str << std::endl;
}

pplx::task<void> GetBlogPageAsync()
{
    using web::http::client::http_client;
    using web::http::methods;
    using web::http::http_response;

    // ??? Why the content_length of http://www.wisenheimerbrainstorm.com/apps/3d-curves-app/ is 0?

    http_client client(U("http://www.gregcons.com"));

    // Request the page download. The client.request() method returns a task.
    return client.request(
        methods::POST,  // an http verb
        U("Kateblog/") // a relative path to the desired resource
    ).then(
        [](http_response response)
    {
        // The following code is excuted once the page has been downloaded.

        auto status{ response.status_code() };
        cout << "Status:" << status << " ";

        auto bodylength = response.headers().content_length();
        cout << "Length:" << bodylength << " ";
    });
}

int main()
{
    SerializeJson();

    // The GetBlogPageAsync returns immediately. On the other hand, 
    // the task it has started continues. That's why we need to wait 
    // for the task to complete.
    GetBlogPageAsync().wait();

    _getch();

    return 0;
}
