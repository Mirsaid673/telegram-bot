#pragma once

#include <string>
#include <curl/curl.h>
#include <iostream>
#include <fstream>

static size_t writer(char *buffer, size_t size, size_t nmemb, std::string *data)
{
    int bytes = 0;
    if (buffer != nullptr)
    {
        bytes = size * nmemb;
        data->append(buffer, bytes);
    }

    return bytes;
}

std::string getUrl(const std::string &url)
{
    CURL *curl;
    curl = curl_easy_init();
    if (curl == nullptr)
    {
        std::cout << "curl not initialized" << std::endl;
        return std::string();
    }

    std::string data;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
    CURLcode res = curl_easy_perform(curl);
    if (res)
    {
        std::cout << "something went wrong; error code: " << res << std::endl;
        return std::string();
    }

    curl_easy_cleanup(curl);

    return data;
}

std::string getPictureUrl(const std::string &name)
{
    std::string url = "https://www.google.com/search?q=banana&tbm=isch";
    std::string html = getUrl("https://www.google.com/search?q=" + name + "&tbm=isch");
    std::string picture_url;

    bool first = true;
    for (size_t i = 0; i < html.size(); i++)
    {
        if (html[i] != 's' || html[i + 1] != 'r' || html[i + 2] != 'c')
            continue;

        if (first)
        {
            first = false;
        }
        else // we found it
        {
            i += 5;
            while (html[i] != '\"')
            {
                picture_url.push_back(html[i]);
                i++;
            }
            break;
        }
    }

    return picture_url;
}

int loadPicture(const std::string &name)
{
    std::string picture_url = getPictureUrl(name);
    std::string image = getUrl(picture_url);

    std::ofstream file("image.jpg");
    if(!file)
    {
        std::cout << "could not create image file" << std::endl;
        return -1;
    }
    
    file << image;

    return 0;
}