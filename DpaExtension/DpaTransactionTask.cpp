#include "DpaTransactionTask.h"
#include <chrono>

DpaTransactionTask::DpaTransactionTask(DpaTask& dpaTask)
  :m_dpaTask(dpaTask)
  ,m_error(0)
{
  m_future = m_promise.get_future();
}

DpaTransactionTask::~DpaTransactionTask()
{
}

const DpaMessage& DpaTransactionTask::getMessage() const
{
  return m_dpaTask.getRequest();
}

int DpaTransactionTask::getTimeout() const
{
  return m_dpaTask.getTimeout();
}

void DpaTransactionTask::processConfirmationMessage(const DpaMessage& confirmation)
{
  m_dpaTask.parseResponse(confirmation);
}

void DpaTransactionTask::processResponseMessage(const DpaMessage& response)
{
  m_error = response.DpaPacket().DpaResponsePacket_t.ResponseCode;
  m_dpaTask.parseResponse(response);
}

void DpaTransactionTask::processFinish(DpaRequest::DpaRequestStatus status)
{
  m_promise.set_value(isProcessed(status));
}

int DpaTransactionTask::waitFinish(unsigned millis)
{
  std::chrono::milliseconds span(millis);
  if (m_future.wait_for(span) == std::future_status::timeout) {
    m_error = -2;
  }
  else {
    m_error = m_future.get() ? m_error : -1;
  }
  return m_error;
}

int DpaTransactionTask::getError() const
{
  return m_error;
}

std::string DpaTransactionTask::getErrorStr() const
{
  switch (m_error) {
  case -2:
    return "ERROR_PROMISE_TIMEOUT";
  case -1:
    return "ERROR_TIMEOUT";
  case STATUS_NO_ERROR:
    return "STATUS_NO_ERROR";
  case ERROR_FAIL:
    return "ERROR_FAIL";
  case ERROR_PCMD:
    return "ERROR_PCMD";
  case ERROR_PNUM:
    return "ERROR_PNUM";
  case ERROR_ADDR:
    return "ERROR_ADDR";
  case ERROR_DATA_LEN:
    return "ERROR_DATA_LEN";
  case ERROR_DATA:
    return "ERROR_DATA";
  case ERROR_HWPID:
    return "ERROR_HWPID";
  case ERROR_NADR:
    return "ERROR_NADR";
  case ERROR_IFACE_CUSTOM_HANDLER:
    return "ERROR_IFACE_CUSTOM_HANDLER";
  case ERROR_MISSING_CUSTOM_DPA_HANDLER:
    return "ERROR_MISSING_CUSTOM_DPA_HANDLER";
  case ERROR_USER_TO:
    return "ERROR_USER_TO";
  case STATUS_CONFIRMATION:
    return "STATUS_CONFIRMATION";
  case ERROR_USER_FROM:
  default:
    std::ostringstream os;
    os << std::hex << m_error;
    return os.str();
  }
}