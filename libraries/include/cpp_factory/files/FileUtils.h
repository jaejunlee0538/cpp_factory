//
// Created by ub1404 on 16. 3. 26.
//

#ifndef PLAYGROUND_VELODYNEREADER_H
#define PLAYGROUND_VELODYNEREADER_H
#include <string.h>
#include <vector>
#include <algorithm>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/regex.hpp>
#include <boost/ref.hpp>
#include <boost/bind.hpp>
#include <boost/config.hpp>
#include <boost/lexical_cast.hpp>
namespace cpp_factory {
    class GetNumberOfFiles {
    public:
        int operator()(const std::string &dir, bool recursive = false) {
            int n_files = 0;

            if (!boost::filesystem::is_directory(dir))
                return -1;

            if (recursive) {
                for (boost::filesystem::directory_iterator it(dir), f_end; it != f_end; it++) {
                    n_files++;
                }
            } else {
                for (boost::filesystem::directory_iterator it(dir), f_end; it != f_end; it++) {
                    n_files++;
                }
            }
            return n_files;
        }
    };

//class ReportGetFilesList{
//public:
//    void operator()(std::ostream& os, PathVector& path_vector){
//        os<<"Total "<< path_vector.size()<<" files are found"<<std::endl;
//        BOOST_FOREACH(boost::filesystem::path p, path_vector){
//                        os<<p.stem().string()<<std::endl;
//                    }
//    }
//};



/*
 * Sort using only file names(excluding extension)
 */
    struct SortByName {
        SortByName(bool ascending = true) : ascending_order(ascending) {
        }

        bool operator()(const boost::filesystem::path &p1, const boost::filesystem::path &p2) {
            if (ascending_order)
                return p1.stem().string() < p2.stem().string();
            else
                return p1.stem().string() > p2.stem().string();
        }

    protected:
        bool ascending_order;
    };

/*
 * Sort using only file names(excluding extension)
 */
    struct SortByExtension {
        SortByExtension(bool ascending = true) : ascending_order(ascending) {
        }

        bool operator()(const boost::filesystem::path &p1, const boost::filesystem::path &p2) {
            if (ascending_order)
                return p1.extension().string() < p2.extension().string();
            else
                return p1.extension().string() > p2.extension().string();
        }

    protected:
        bool ascending_order;
    };

/*
 *
 */
    struct SortByDigitsInName{
        SortByDigitsInName(const std::string& regex= "[0-p]+", bool ascending = true) :
                ascending_order(ascending), e(regex){ }

        bool operator()(const boost::filesystem::path &p1, const boost::filesystem::path &p2) {
            boost::smatch sm1, sm2;
            if(boost::regex_search(p1.stem().string(), sm1, e) && boost::regex_search(p2.stem().string(), sm2, e)){
                if(ascending_order)
                    return boost::lexical_cast<int>(sm1[0]) < boost::lexical_cast<int>(sm2[0]);
                else
                    return boost::lexical_cast<int>(sm1[0]) > boost::lexical_cast<int>(sm2[0]);
            }

            std::ostringstream ss;
            ss<<"No digits in the file names("<<p1.stem()<<" vs "<<p2.stem()<<")";
            throw std::runtime_error(ss.str());
        }
        boost::regex e;
        bool ascending_order;
    };

#ifndef BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
/*
 * Perl Regular Expression Syntax :
 *      http://www.boost.org/doc/libs/1_60_0/libs/regex/doc/html/boost_regex/syntax/perl_syntax.html
 */

    class FilesList : public std::vector<boost::filesystem::path> {
    public:

        template <class FileSorterT=SortByName> //default sorter(SortByName)
        FilesList(const std::string &dir, const std::string &f_regex, FileSorterT fileSorter) {
            //TODO : Default value for template is only availible in c++11.
            boost::regex e(f_regex, boost::regex::perl);
            boost::filesystem::path path(dir);
            if (!boost::filesystem::is_directory(path)) {
                throw std::runtime_error(path.string() + std::string(" is not a directory\n"));
            }

            for (boost::filesystem::directory_iterator file(path), f_end; file != f_end; ++file) {
                if (boost::regex_match(file->path().filename().string(), e))
                    this->push_back(file->path());
            }

            std::sort(this->begin(), this->end(), fileSorter);
        }
    };

#endif
/*
 * RegexForFileExtension regex("png");//(
 */
    struct RegexForFileExtension : public std::string {
        RegexForFileExtension(const std::string &extension)
                : std::string(".+\\.(" + extension + "){1}") { }
    };

/*
 * RegexForFileExtensions regex("png,jpg,bmp");
 */
    struct RegexForFileExtensions : public std::string {
    /*
     * Input:
     *  extensions : extension(s) separated by ','
     */
        RegexForFileExtensions(const std::string &extensions) {
            std::string tmp_str = extensions;
            int pos;
            const char str[] = "|";
            pos = tmp_str.find_first_of(',');

            while ((pos = tmp_str.find_first_of(',')) != tmp_str.npos) {
                tmp_str.replace(pos, 1, str);
            }
            this->assign(".+\\.(" + tmp_str + "){1}");
        }

        /*
         * Input:
         *  extensions : a vector of extensions(s)
         */
        RegexForFileExtensions(const std::vector<std::string>& extensions){
            std::string tmp_str;
            std::string str_or="|";
            assert(extensions.size()>0);
            tmp_str += extensions[0];
            for(int i=1;i<extensions.size();i++){
                tmp_str+=str_or;
                tmp_str += extensions[i];
            }
            this->assign(".+\\.(" + tmp_str + "){1}");
        }
    };
}
#if defined(__linux__)
#include <pwd.h>
#include <ctime>
namespace cpp_factory{

    struct LinuxHomeDir:public std::string{
        LinuxHomeDir(){
            passwd* pw = getpwuid(getuid());
            this->assign(pw->pw_dir);
        }
    };

    struct FileNameWithTimeStamp:public std::string{
        enum TimeStampFormat{
            YYYYMMDD_hhmmss = 1,
            YYYYMMDD,
            hhmmss
        };

        FileNameWithTimeStamp(const std::string& extension, const std::string& file_name="", TimeStampFormat fmt=YYYYMMDD_hhmmss){
            time_t rawtime;
            struct tm* timeinfo;
            time(&rawtime);
            timeinfo = localtime(&rawtime);

            char buffer[80];
            switch(fmt){
                case YYYYMMDD_hhmmss:
                    strftime(buffer,80,"%Y-%m-%d_%I:%M:%S", timeinfo);
                    break;
                case YYYYMMDD:
                    strftime(buffer,80,"%Y-%m-%d", timeinfo);
                    break;
                case hhmmss:
                    strftime(buffer,80,"%I:%M:%S", timeinfo);
                    break;
            }
            std::string stamp(buffer);
            if(!file_name.empty())
                this->assign(file_name+"_"+ stamp);
            else
                this->assign(stamp);

            *this += ".";
            *this += extension;
        }
    };

}
#endif
#endif //PLAYGROUND_VELODYNEREADER_H
