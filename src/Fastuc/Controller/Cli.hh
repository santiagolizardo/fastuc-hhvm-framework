<?hh // strict
namespace Fastuc\Controller;

abstract class Cli
{
	/**
	 * @param array $args
	 */
	abstract public static function main( array $args );
}

