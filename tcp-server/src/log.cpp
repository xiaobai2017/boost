#include "log.h"
#include <stdexcept>
#include <string>
#include <iostream>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/trivial.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/log/support/date_time.hpp>

namespace logging = boost::log;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;
using boost::shared_ptr;

void Log::Init(const std::string & dir)
{
    try
    {
    	//Create a console log
    	logging::add_console_log(std::clog,
    			keywords::format =
    			(
    					expr::stream
						<< std::setw(3) << std::setfill(' ') << expr::attr< unsigned int >("LineID")
						<< ": ["
						//<< expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S")
						<< expr::attr< boost::posix_time::ptime >("TimeStamp")
						<< "] ["
						<< expr::attr< attrs::current_thread_id::value_type >("ThreadID")
						<<"] <"
						<< logging::trivial::severity
						<< "> " << expr::smessage
					) );

        // Create a text file sink
        typedef sinks::synchronous_sink< sinks::text_file_backend > file_sink;
        shared_ptr< file_sink > sink(new file_sink(
            keywords::file_name = dir + "/%Y%m%d_%H%M%S_%3N.log",      // file name pattern
            keywords::rotation_size = 10 * 1024 * 1024,                    // rotation size 10M, in characters
			keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0)
            ));

        // Set up where the rotated files will be stored
        sink->locked_backend()->set_file_collector(sinks::file::make_collector(
            keywords::target = dir,                          // where to store rotated files
            keywords::max_size = 1024 * 1024 * 1024,         //1G     // maximum total size of the stored files, in bytes
            keywords::min_free_space = 100 * 1024 * 1024,       // minimum free space on the drive, in bytes
            keywords::max_files = 256                           // maximum number of stored files
            ));

        // Upon restart, scan the target directory for files matching the file_name pattern
        sink->locked_backend()->scan_for_files(sinks::file::scan_matching, true);

#if 0
        sink->set_formatter
        (
            expr::format("%1%:[%2%] <%3%> %4%")
                % expr::attr< unsigned int >("LineID")
                % expr::attr< boost::posix_time::ptime >("TimeStamp")
				% logging::trivial::severity
                % expr::smessage
        );
#endif
        sink->set_formatter
        (
            expr::stream
                << std::setw(3) << std::setfill(' ') << expr::attr< unsigned int >("LineID")
				<< ": ["
                //<< expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S")
				<< expr::attr< boost::posix_time::ptime >("TimeStamp")
				<< "] ["
				<< expr::attr< attrs::current_thread_id::value_type >("ThreadID")
                <<"] <"
				<< logging::trivial::severity
                << "> " << expr::smessage
        );

        sink->locked_backend()->auto_flush(true);

        // Add it to the core
        logging::core::get()->add_sink(sink);

        // Add attributes
        logging::add_common_attributes();

        // Add some attributes too
        //logging::core::get()->add_thread_attribute("Scope", attrs::named_scope());
        //logging::core::get()->add_global_attribute("TimeStamp", attrs::local_clock());
        //logging::core::get()->add_global_attribute("RecordID", attrs::counter< unsigned int >());

    }
    catch (std::exception& e)
    {
        std::cout << "FAILURE: " << e.what() << std::endl;
    }
}

