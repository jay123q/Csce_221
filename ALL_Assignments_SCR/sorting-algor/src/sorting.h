#pragma once

#include <functional> // std::less
#include <iterator>
// #include <chrono> 
// This is C++ magic which will allows our function
// to default to using a < b if the comparator arg
// is unspecified. It uses defines std::less<T>
// for the iterator's value_type.
//
// For example: if you have a vector<float>, the 
// iterator's value type will be float. std::less 
// will select the < for sorting floats as the 
// default comparator.

namespace sort {
	template<typename RandomIter>
	using less_for_iter = std::less<typename std::iterator_traits<RandomIter>::value_type>;

	/* Efficiently swap two items - use this to implement your sorts */
	template<typename T>
	void swap(T & a, T & b) noexcept
	{ 
		//T c(a);
		T c = std::move(a);
		a=std::move(b);
		b=std::move(c);	
	}

	template<typename RandomIter, typename Comparator = less_for_iter<RandomIter>>
	void bubble(RandomIter begin, RandomIter end, Comparator comp = Comparator{}) {
		// Random access iterators have the same traits you defined in the Vector class
		// For instance, difference_type represents an iterator difference
		// // You may delete the types you don't use to remove the compiler warnings
		// using _it             = std::iterator_traits<RandomIter>;
		// using difference_type = typename _it::difference_type;
		// using value_type      = typename _it::value_type;
		// using reference       = typename _it::reference;
		// using pointer         = typename _it::pointer;
		// chrono found on https://www.geeksforgeeks.org/chrono-in-c/
	//	difference_type = begin;
    // auto start = high_resolution_clock::now();

	// this is a simple sort got from tas
	// for(RandomIter a = abab ; a < end12 ; a++)
	// {
	// 	for(RandomIter b = abab ; b < a; b++)
	// 	{
	// 		if(comp(*a,*b))
	// 		{
	// 			swap(*a,*b);
	// 		}
	// 	}
	// }
    // auto stop = high_resolution_clock::now();
    // auto duration = duration_cast<microseconds>(stop - start);
	//	std::cout << " the total time is " << duration.count() << " seconds! " << std::endl;

	// bool Gate = true;
    // for (RandomIter index1 = abab; index1<end12; ++index1)
	// {
//    auto start = std::chrono::high_resolution_clock::now();

		RandomIter index1 = begin;
		while(index1<end)
		{
			RandomIter index2 = index1+1;
			while(index2<end)
			{
			//	std::cout << " am r" << std::endl;
				if(comp(*index2,*index1))
				{
					swap(*index2,*index1);
				}
				index2++;
			}
			index1++;
		}
    // auto stop = high_resolution_clock::now();
    // auto duration = duration_cast<microseconds>(stop - start);
	// std::cout << " the total time is " << duration.count() << " seconds! " << std::endl;

		// this is stack overflow and class notes help
	    //auto start = std::chrono::high_resolution_clock::now();

    //     for (RandomIter index2 =index1+1; Gate; ++index2)
	// 	{
    //         if (comp(* (index2),*index1))
    //             {
	// 				std::iter_swap( index2, index1);
	// 			}
	// 		if(index2<end12)
	// 		{
	// 			// keep running
	// 			Gate = true;
	// 		}
	// 		else{Gate = false;}
	//	}
    // auto stop = high_resolution_clock::now();
    // auto duration = duration_cast<microseconds>(stop - start);
	// std::cout << " the total time is " << duration.count() << " seconds! " << std::endl;

	//     auto start = std::chrono::high_resolution_clock::now();

	// what we helped ian with
    // for (RandomIter index1 = abab; index1<end12; ++index1)
	// {

    //     for (RandomIter index2 =index1+1; index2<end12; ++index2)
	// 	{
	// 		//std::cout<<"hi"<< std::endl;
    //         if (comp(* (index2),*index1))
    //             {
	// 				std::iter_swap( index2, index1);
	// 			}
	// 	}
	// }
    // auto stop = high_resolution_clock::now();
    // auto duration = duration_cast<microseconds>(stop - start);
	// std::cout << " the total time is " << duration.count() << " seconds! " << std::endl;




		// COMPLETE
	//}
}

	template<typename RandomIter, typename Comparator = less_for_iter<RandomIter>>
	void insertion(RandomIter begin, RandomIter end, Comparator comp = Comparator{}) 
	{ 
		/* COMPLETE */
	//	std::swap(*begin,std::min_element(begin,end,comp));
		// temp = std::min_element(begin,end,comp);
		// std::swap(*begin,*temp);
				//6,4,10,8,1
		// 1,4,10,8,6
		//1,4,10,8,6
		//1,4,6,8,10
		//
		//-8,13,-11

		for(RandomIter Awooga = begin+1 ; Awooga < end ; Awooga++)
		{
			RandomIter tmp = Awooga;
			RandomIter J = Awooga;
			for( ; J>begin && comp(*J, *(J-1)); J--)
			{
				swap(*J,*(J-1));

			}
			Awooga = tmp;
			// std::cout<<"swap " << *box << " with " << *Awooga << std::endl;
			// swap(*box,*Awooga);


	
		//std::iter_swap(begin,begin+1);
		}

	// void Printer(RandomIter begin, RandomIter end)
	// {
	// 			for(RandomIter a = begin ; a !=end;a++)
	// 	{
	// 		std::cout<<*a<<std::endl;
	// 	}
	// }

	}

	template<typename RandomIter, typename Comparator = less_for_iter<RandomIter>>
	void selection(RandomIter begin, RandomIter end, Comparator comp = Comparator{}) 
	{
		RandomIter box;
		for(RandomIter index = begin ; index != end; index++)
		{
			box = std::min_element(index,end,comp);
			swap(*index,*box);


		}
	// 		box = std::min_element(index,end);
	// 		std::iter_swap(box,index);
	// 		// box = index;
	// 		// if(comp(*box,*index))
	// 		// 	{swap(*index,*box);}
	// 	}
	// //	comp(*box,*index);
		 if(1)
		 {
	// 	// for(RandomIter k = begin ; k !=end-1 ; k++)
	// 	// {
	// 	// 	RandomIter index = k;
	// 	// 	for(RandomIter i = k + 1 ; i != end ; i++)
	// 	// 	{
	// 	// 		if(comp(*i,*index))
	// 	// 		{
	// 	// 			index = i;
	// 	// 		}
	// 	// 	}
	// 	// 	std::swap(*k,*index);
	// 	// }
	// 	// for( RandomIter index1 = begin ; index1 < end -1 ; index1 ++ )
	// 	// {
	// 	// 	std::cout << " ping " <<std::endl;
	// 	// 	RandomIter OhStoreSomethingBigInMe = index1; 
	// 	// 	for( RandomIter index2 = index1 + 1; index2 < end ; index2++)
	// 	// 	{
	// 	// 		std::cout << " pong " << std::endl;
	// 	// 		if(comp(* index2,* OhStoreSomethingBigInMe))
	// 	// 		{
	// 	// 			std::cout << "ping pong " << std::endl;

	// 	// 			OhStoreSomethingBigInMe = index2;
	// 	// 		}
	// 	// 	}
	// 	// 	std::cout << "ping pong2 " << std::endl;
	// 	// 	RandomIter c = std::move(OhStoreSomethingBigInMe);
	// 	// 	OhStoreSomethingBigInMe =std::move(index1);
	// 	// 	index1 = std::move(c);
	// 		//std::swap(* index1,* OhStoreSomethingBigInMe);
	// // 	}
	 	 }
	   
	}
	// RandomIter min_element(RandomIter index,RandomIter end, Comparator box=Comparator{})
	// {

	// 	RandomIter box = index;
	// 	for(RandomIter DanteDaddy = index ; DanteDaddy != end ; DanteDaddy++)
	// 	{
	// 		if(comp(box,DanteDaddy))(box=DanteDaddy;)
	// 	}
	// 	return box;
	// }


}



