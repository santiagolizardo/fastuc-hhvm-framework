<?hh // strict
namespace Fastuc;

/**
 * The Registry class is a global variable storage. (similar to $_GLOBALS, but safer).
 */
class Registry extends \Fastuc\Utils\TypedArray
{
	/**
	 * @var \Fastuc\Registry
	 */
	private static \Fastuc\Registry $singleton = null;

	/**
	 * @return \Fastuc\Registry
	 */
	public static function getInstance() : this
	{
		if( null === self::$singleton )
		{
			self::$singleton = new self;
		}

		return self::$singleton;
	}
}

