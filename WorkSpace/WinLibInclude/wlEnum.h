
#pragma once

//
// @brief ��������ö����
//
enum wlProcessFeature {
	// ��ֹ����
	WL_PROCESS_FEATURE_TERMINATE = (1 << 0),
	// ��ѯ������Ϣ
	WL_PROCESS_FEATURE_QUERY_INFO = (1 << 2),
	// ���ݽ��������ڴ�
	WL_PROCESS_FEATURE_VM_OPERATION = (1 << 3),
};
