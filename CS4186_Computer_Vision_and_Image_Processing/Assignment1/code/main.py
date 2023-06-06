import utils
from CNN import CnnImageSearcher
from SIFT_Color import CombinedImageSearcher


def main():
    test = False
    image_path = '../ug_data/database/'
    query_path = '../ug_data/examples/' if test else '../ug_data/query/'
    features_path = './features/'
    res_path = '../query_result/'


    # The mode you want to apply:
    # Option 1: "Color_hist"
    # Option 2: "SIFT"

    # mode = 'SIFT_Color_Hist'
    mode = 'CNN'
    result_lists = list()

    if mode == 'CNN':
        print("Using CNN.")
        data_loader = utils.load_data(image_path, mode = mode)
        query_loader = utils.load_data(query_path, mode = mode)

        searcher = CnnImageSearcher()

        print("Start to convert all image data.")
        data_feature_list, data_filename_list = \
                    searcher.extract_features(data_loader)

        print("Start to process the queries.")
        result_lists = searcher.image_search(query_loader, data_feature_list, data_filename_list)

    elif mode == 'SIFT_Color_Hist':
        print("Using combined method.")
        data = utils.load_data(image_path + 'Images/', mode = mode)
        dir_name = 'example_query/' if test else 'Images/'
        query = utils.load_data(query_path + dir_name, mode = mode)
        searcher = CombinedImageSearcher()

        print("Start to convert all image data.")
        data_feature = searcher.extract_features(data)
        query_feature = searcher.extract_features(query)

        print("Start to process the queries.")
        result_lists = searcher.image_search(query_feature, data_feature)
    result_type = 'test' if test else 'query' 
    utils.save_result(result_lists, res_path+ result_type +'_result_'+mode+'.txt')
    print("Finished!")


if __name__ == "__main__":
    main()