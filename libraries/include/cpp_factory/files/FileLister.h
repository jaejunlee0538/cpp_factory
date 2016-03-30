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

    struct FileSorter {
        virtual ~FileSorter() { }

        virtual bool operator()(const boost::filesystem::path &p1, const boost::filesystem::path &p2) const = 0;
    };

/*
 * Sort using only file names(excluding extension)
 */
    struct SortByName : public FileSorter {
        SortByName(bool ascending = true) : ascending_order(ascending) {
        }

        virtual bool operator()(const boost::filesystem::path &p1, const boost::filesystem::path &p2) const {
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
    struct SortByExtension : public FileSorter {
        SortByExtension(bool ascending = true) : ascending_order(ascending) {
        }

        virtual bool operator()(const boost::filesystem::path &p1, const boost::filesystem::path &p2) const {
            if (ascending_order)
                return p1.extension().string() < p2.extension().string();
            else
                return p1.extension().string() > p2.extension().string();
        }

    protected:
        bool ascending_order;
    };

/*
 * Perl Regular Expression Syntax :
 *      http://www.boost.org/doc/libs/1_60_0/libs/regex/doc/html/boost_regex/syntax/perl_syntax.html
 */
    class FilesList : public std::vector<boost::filesystem::path> {
    public:
        FilesList(const std::string &dir, const std::string &f_regex, const FileSorter &fileSorter = SortByName()) {
            boost::regex e(f_regex, boost::regex::perl);
            boost::filesystem::path path(dir);
            if (!boost::filesystem::is_directory(path)) {
                throw std::runtime_error(path.string() + std::string(" is not a directory\n"));
            }

            for (boost::filesystem::directory_iterator file(path), f_end; file != f_end; ++file) {
                if (boost::regex_match(file->path().filename().string(), e))
                    this->push_back(file->path());
            }

            std::sort(this->begin(), this->end(), boost::bind<bool>(boost::ref(fileSorter), _1, _2));
        }
    };


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
    };
}
#endif //PLAYGROUND_VELODYNEREADER_H
