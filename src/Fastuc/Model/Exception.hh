<?hh // strict
namespace Fastuc\Model;

/**
 * An exception containing extra information about the error occured in the model.
 */
class Exception extends \Exception
{
	/**
	 * @var \mysqli
	 */
	private $db;

	/**
	 * @param \mysqli $db
	 * @param string $message
	 */
	public function __construct( \mysqli $db, string $message = null )
	{
		$this->db = $db;

		parent::__construct( $db->error . ': ' . $message );
	}
}

