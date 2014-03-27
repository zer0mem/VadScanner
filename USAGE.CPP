EPROCESS* eprocess = reinterpret_cast<EPROCESS*>(PsGetCurrentProcess());

		VadTree::iterator it;

		CMMVadShort* vad_root = reinterpret_cast<CMMVadShort*>(eprocess->VadRoot());
		it->MMADDRESS_NODE.right_ = vad_root->MMADDRESS_NODE.right_;
		it->MMADDRESS_NODE.parent_ = vad_root->MMADDRESS_NODE.parent_;

		for (int i = 0; i < 0x10; i++)
		{
			MMVAD_SHORT* vad = *(++it);
			DbgPrint("\n%p %i %p %p %p %p\n", it, i, vad->StartingVpn(), vad->EndingVpn(), &vad->StartingVpn());
		}



//NEW USAGE!!
		CRange<void*> mem(nullptr);
		if (CVAdScanner::GetMemory((void*)0x77000000, &mem))
		{
			DbgPrint("\nfound memory : %p %p\n", mem.Begin(), mem.End());
		
			std::shared_ptr<CVadNode> sp_vad_node;
			if (!CVAdScanner::Find(mem, &sp_vad_node))
				return;

			for (int i = 0; i < 0x10; i++)
			{
				++(*sp_vad_node.get());
				DbgPrint("\na. %p ITERATE : %p %p\n", sp_vad_node.get(), sp_vad_node->Begin(), sp_vad_node->End());
			}
		}