#include "Compression.hpp"

#define MINIZ_HEADER_FILE_ONLY
#include "../ExtLibs/miniz.c"

namespace ke
{

const std::string base64_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                 "abcdefghijklmnopqrstuvwxyz"
                                 "0123456789+/";

bool base64_encode(std::string& data)
{
    int count = 0;
    unsigned char input_bytes[3] = { '\0', '\0', '\0' };
    unsigned char byte_array[4];
    std::string result;
    for (unsigned int i = 0; i < data.size(); ++i)
    {
        input_bytes[count++] = data[i];
        if (count == 3 || (i == data.size() - 1))
        {
            byte_array[0] = input_bytes[0] >> 2;
            byte_array[1] = ((input_bytes[0] & 0x3) << 4) | (input_bytes[1] >> 4);
            byte_array[2] = ((input_bytes[1] & 0xf) << 2) | (input_bytes[2] >> 6);
            byte_array[3] = input_bytes[2] & 0x3f;
            memset(input_bytes, '\0', 3);
            for (int j = 0; j < count + 1; j++)
                result += base64_table[byte_array[j]];
            if (count != 3)
                for (int i = count; i < 3; ++i)
                    result += '=';
            else
                count = 0;
        }
    }
    data = result;
    return true;
}

bool base64_decode(std::string& data)
{
    int count = 0;
    unsigned char input_bytes[4] = { '\0', '\0', '\0', '\0' };
    unsigned char byte_array[3];
    std::string result;
    for (unsigned int i = 0; i < data.size(); ++i)
    {
        if (is_valid_base64(data[i]))
            input_bytes[count++] = static_cast<unsigned char>(base64_table.find(data[i]));
        if (count == 4 || data[i] == '=')
        {
            byte_array[0] = (input_bytes[0] << 2) | ((input_bytes[1] & 0x30) >> 4);
            byte_array[1] = ((input_bytes[1] & 0xf) << 4) | ((input_bytes[2] & 0x3c) >> 2);
            byte_array[2] = ((input_bytes[2] & 0x3) << 6) | input_bytes[3];
            memset(input_bytes, '\0', 4);
            for (int j = 0; j < count - 1; j++)
                result += byte_array[j];
            if (count != 4)
                break;
            else
                count = 0;
        }
    }
    data = result;
    return true;
}

bool decompressString(std::string& data)
{
    mz_stream zstream;
    std::string outstring;
    zstream.zalloc = 0;
    zstream.zfree = 0;
    zstream.opaque = 0;
    zstream.next_in = const_cast<unsigned char*>(reinterpret_cast<const unsigned char*>(data.data()));
    zstream.avail_in = data.size();
    int result;
    result = mz_inflateInit(&zstream);
	char outbuffer[32768];
    if (result != MZ_OK)
    {
        return false;
    }
    do
    {
        zstream.next_out = reinterpret_cast<unsigned char*>(outbuffer);
        zstream.avail_out = sizeof(outbuffer);
        result = mz_inflate(&zstream, MZ_SYNC_FLUSH);
        switch (result)
        {
            case MZ_NEED_DICT:
            case MZ_STREAM_ERROR:
                result = MZ_DATA_ERROR;
            case MZ_DATA_ERROR:
            case MZ_MEM_ERROR:
                mz_inflateEnd(&zstream);
                return false;
        }
        if (outstring.size() < zstream.total_out)
        {
            outstring.append(outbuffer, zstream.total_out - outstring.size());
        }
    } while (result != MZ_STREAM_END);
    if (zstream.avail_in != 0)
    {
        return false;
    }
    mz_inflateEnd(&zstream);
    data = outstring;
    return true;
}

bool compressString(std::string& data)
{
    mz_stream zs; // z_stream is zlib's control structure
    memset(&zs, 0, sizeof(zs));
    if (mz_deflateInit(&zs, MZ_BEST_COMPRESSION) != MZ_OK)
    {
        return false;
    }
    zs.next_in = (unsigned char*)data.data();
    zs.avail_in = data.size(); // set the z_stream's input
    int ret;
    char outbuffer[32768];
    std::string outstring;
    // retrieve the compressed bytes blockwise
    do
    {
        zs.next_out = reinterpret_cast<unsigned char*>(outbuffer);
        zs.avail_out = sizeof(outbuffer);
        ret = mz_deflate(&zs, MZ_FINISH);
        if (outstring.size() < zs.total_out)
        {
            // append the block to the output string
            outstring.append(outbuffer, zs.total_out - outstring.size());
        }
    } while (ret == MZ_OK);
    mz_deflateEnd(&zs);
    if (ret != MZ_STREAM_END) // an error occurred that was not EOF
    {
        return false;
    }
    data = outstring;
    return true;
}

bool compress64(std::string& data)
{
    std::string d = data;
    if (compressString(d))
    {
        if (base64_encode(d))
        {
            data = d;
            return true;
        }
    }
    return false;
}

bool decompress64(std::string& data)
{
    std::string d = data;
    if (base64_decode(d))
    {
        if (decompressString(d))
        {
            data = d;
            return true;
        }
    }
    return false;
}

void loadCompressedXml(std::string const& filename, pugi::xml_document& doc)
{
    std::ifstream iFile(filename);
    std::ofstream oFile(".temp");
    if (iFile && oFile)
    {
        std::string s;
        while (std::getline(iFile,s))
        {
            decompress64(s);
            oFile << s << std::endl;
        }
    }
    iFile.close();
    oFile.close();

    doc.load_file(".temp");

    remove(".temp");
}

void saveCompressedXml(std::string const& filename, pugi::xml_document const& doc)
{
    doc.save_file(".temp");

    std::ifstream iFile(".temp");
    std::ofstream oFile(filename);
    if (iFile && oFile)
    {
        std::string s;
        while (std::getline(iFile,s))
        {
            compress64(s);
            oFile << s << std::endl;
        }
    }
    iFile.close();
    oFile.close();

    remove(".temp");
}

} // namespace ke