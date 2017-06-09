/*
 * log.h
 *
 *  Requirement: boost_1_64_0 version library
 *  Created on: 2017/05/19
 *      Author: xiaobai
 */

#ifndef LOG_H_
#define LOG_H_

#define BOOST_LOG_DYN_LINK 1
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/trivial.hpp>

#define FUNC_LINE_COUT \
	<<"[" << __FUNCTION__  << ":" << __LINE__ <<"] "
	//<<"["<< __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ <<"] "

#define LOG_TRACE\
    BOOST_LOG_SEV((my_g_logger::get()), (boost::log::trivial::trace))

#define LOG_DEBUG\
    BOOST_LOG_SEV((my_g_logger::get()), (boost::log::trivial::debug))

#define LOG_INFO\
    BOOST_LOG_SEV((my_g_logger::get()), (boost::log::trivial::info))

#define LOG_WARNING\
    BOOST_LOG_SEV((my_g_logger::get()), (boost::log::trivial::warning))

#define LOG_ERROR\
    BOOST_LOG_SEV((my_g_logger::get()), (boost::log::trivial::error))

#define LOG_TRACE_F\
    BOOST_LOG_SEV((my_g_logger::get()), (boost::log::trivial::trace)) FUNC_LINE_COUT

#define LOG_DEBUG_F\
    BOOST_LOG_SEV((my_g_logger::get()), (boost::log::trivial::debug)) FUNC_LINE_COUT

#define LOG_INFO_F\
    BOOST_LOG_SEV((my_g_logger::get()), (boost::log::trivial::info)) FUNC_LINE_COUT

#define LOG_WARNING_F\
    BOOST_LOG_SEV((my_g_logger::get()), (boost::log::trivial::warning)) FUNC_LINE_COUT

#define LOG_ERROR_F\
    BOOST_LOG_SEV((my_g_logger::get()), (boost::log::trivial::error)) FUNC_LINE_COUT

BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(my_g_logger, boost::log::sources::severity_logger_mt< boost::log::trivial::severity_level >)

class Log
{
public:
	// 若要使用文件日志，请先在main函数中调用该自定义初始化函数
	static void Init(const std::string & dir);
};

#endif /* LOG_H_ */
