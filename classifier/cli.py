# cli.py
import argparse
import sys
import json
from pipeline.language_inferencer import LanguageInferencer
from pipeline.trainer import ModelTrainer

def main():
    parser = argparse.ArgumentParser(description='Binary Language Classifier')
    subparsers = parser.add_subparsers(dest='command', help='Commands')
    
    # Analyze command
    analyze_parser = subparsers.add_parser('analyze', help='Analyze a binary')
    analyze_parser.add_argument('binary', help='Path to binary file')
    analyze_parser.add_argument('--model', help='Path to trained model', default='model.pkl')
    analyze_parser.add_argument('--format', choices=['json', 'text'], default='json')
    
    # Train command
    train_parser = subparsers.add_parser('train', help='Train a model')
    train_parser.add_argument('dataset', help='Path to dataset directory')
    train_parser.add_argument('--output', help='Output model path', default='language_classifier.pkl')
    
    args = parser.parse_args()
    
    if args.command == 'analyze':
        inferencer = LanguageInferencer(model_path=args.model)
        result = inferencer.analyze_binary(args.binary)
        
        if args.format == 'json':
            print(json.dumps(result, indent=2))
        else:
            print("\nLanguage Probabilities:")
            for lang, prob in sorted(result.items(), key=lambda x: x[1], reverse=True):
                if lang != 'confidence':
                    print(f"  {lang}: {prob:.3f}")
            print(f"\nConfidence: {result['confidence']:.3f}")
    
    elif args.command == 'train':
        print("Trainer File Not Available")
        trainer = ModelTrainer(args.dataset)
        classifier, score = trainer.train_and_evaluate(args.output)
        print(f"Model trained and saved to {args.output}")
        print(f"Test accuracy: {score:.3f}")
    
    else:
        parser.print_help()

if __name__ == '__main__':
    main()