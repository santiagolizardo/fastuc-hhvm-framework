<?hh // strict
namespace Fastuc\Input;

class Filter extends Handler
{
	/**
	 * @var \Fastuc\Input\Http
	 */
	private \Fastuc\Input\Http $params;

	/**
	 * @param \Fastuc\Input\Http $params
	 */
	public function __construct( \Fastuc\Utils\TypedArray $params )
	{
		parent::__construct();

		$this->params = $params;
	}

	public function getValue( string $value, array $validations, mixed $fallback = null, array $transformations = array() ) : mixed
	{
		$value = $this->params->getParam( $value );
		return parent::getValue( $value, $validations, $fallback, $transformations );
	}
}

