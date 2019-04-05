bool List::remove_last()
{
   Node* node_ptr = top;
   Node* previous_node_ptr = nullptr;

   //case 1: nothing in the list;
   if (node_ptr == nullptr)
   {
      cout << "The list is empty! No node to remove." << endl;
      return false;
   }

   //case 2: only one node in the list
   if (node_ptr->get_next() == nullptr)
   {
      delete node_ptr;
      node_ptr = nullptr;
      top = nullptr;
      return true;
   }

   //case 3: multiple nodes in the list
   while (node_ptr->get_next() != nullptr)
   {
      previous_node_ptr = node_ptr;
      node_ptr = node_ptr->get_next();
   }
   delete node_ptr;
   node_ptr = nullptr;
   previous_node_ptr->set_next(nullptr);
   return true;
}